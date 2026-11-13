#pragma once

namespace TicTacToeCpp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		PictureBox^ gameImage;
		Image^ wireImage;
		array<bool, 2>^ markedCells;

	public:
		MyForm(void)
		{
			InitializeComponent();

			wireImage = Image::FromFile(
				System::IO::Path::Combine(
					AppDomain::CurrentDomain->BaseDirectory,
					L"Images\\Wire.png"
				)
			);
			markedCells = gcnew array<bool, 2>(7, 7);
			gameImage = gcnew PictureBox();
			gameImage->Image = Image::FromFile(
				System::IO::Path::Combine(
					AppDomain::CurrentDomain->BaseDirectory,
					L"Images\\7x7_Board_Updated.png"
				)
			);
			gameImage->SizeMode = PictureBoxSizeMode::Zoom;
			gameImage->Dock = DockStyle::Fill;
			gameImage->MouseClick +=
				gcnew MouseEventHandler(this, &MyForm::GameImage_Click);
			gameImage->Paint +=
				gcnew PaintEventHandler(this, &MyForm::GameImage_Paint);

			this->Controls->Add(gameImage);
		}

		void GameImage_Click(Object^ sender, MouseEventArgs^ e)
		{
			double scaleX = (double)gameImage->ClientSize.Width /
				gameImage->Image->Width;

			double scaleY = (double)gameImage->ClientSize.Height /
				gameImage->Image->Height;

			double scale = Math::Min(scaleX, scaleY);

			int displayedWidth = (int)(gameImage->Image->Width * scale);
			int displayedHeight = (int)(gameImage->Image->Height * scale);

			int offsetX = (gameImage->ClientSize.Width - displayedWidth) / 2;
			int offsetY = (gameImage->ClientSize.Height - displayedHeight) / 2;

			// Approximate board boundaries in the original image
			int boardLeft = offsetX + (int)(725 * scale);
			int boardRight = offsetX + (int)(1880 * scale);

			int boardTop = offsetY + (int)(154 * scale);
			int boardBottom = offsetY + (int)(1310 * scale);

			// Ignore clicks outside the board
			if (e->X < boardLeft || e->X >= boardRight ||
				e->Y < boardTop || e->Y >= boardBottom)
				return;

			int column = (e->X - boardLeft) * 7 /
				(boardRight - boardLeft);

			int row = (e->Y - boardTop) * 7 /
				(boardBottom - boardTop);

			markedCells[row, column] = !markedCells[row, column];

			gameImage->Invalidate();
		}

		void GameImage_Paint(Object^ sender, PaintEventArgs^ e)
		{
			double scaleX = (double)gameImage->ClientSize.Width /
				gameImage->Image->Width;

			double scaleY = (double)gameImage->ClientSize.Height /
				gameImage->Image->Height;

			double scale = Math::Min(scaleX, scaleY);

			int displayedWidth = (int)(gameImage->Image->Width * scale);
			int displayedHeight = (int)(gameImage->Image->Height * scale);

			int offsetX = (gameImage->ClientSize.Width - displayedWidth) / 2;
			int offsetY = (gameImage->ClientSize.Height - displayedHeight) / 2;

			int boardLeft = offsetX + (int)(725 * scale);
			int boardRight = offsetX + (int)(1880 * scale);

			int boardTop = offsetY + (int)(154 * scale);
			int boardBottom = offsetY + (int)(1310 * scale);

			double cellWidth = (double)(boardRight - boardLeft) / 7.0;
			double cellHeight = (double)(boardBottom - boardTop) / 7.0;

			for (int row = 0; row < 7; row++)
			{
				for (int column = 0; column < 7; column++)
				{
					if (markedCells[row, column])
					{
						int markerWidth = (int)(cellWidth * 0.65);
						int markerHeight = (int)(cellHeight * 0.65);

						int x = boardLeft + column * cellWidth +
							(cellWidth - markerWidth) / 2;

						int y = boardTop + row * cellHeight +
							(cellHeight - markerHeight) / 2;

						e->Graphics->DrawImage(
							wireImage,
							x,
							y,
							markerWidth,
							markerHeight
						);
					}
				}
			}
		}	

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(1280,720);
			this->Text = L"ABCircuit";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
