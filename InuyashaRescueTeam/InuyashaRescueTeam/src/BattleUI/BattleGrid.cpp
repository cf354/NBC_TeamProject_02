#include "BattleUI/BattleGrid.h"
#include <fstream>
#include <conio.h>



void BattleGrid::Draw()
{
    DrawGrid();
    DrawCharacter();
}

void BattleGrid::SetGrid() {
	_GridTop.append("┌");
	for (int i = 0; i < _GridWidth - 2; i++)
	{
		_GridTop.append("─");
	}
	_GridTop.append("┐");

	_GridMiddle.append("│");
	for (int i = 0; i < _GridWidth - 2; i++)
	{
		_GridMiddle.append(" ");
	}
	_GridMiddle.append("│");

	_GridBottom.append("└");
	for (int i = 0; i < _GridWidth - 2; i++)
	{
		_GridBottom.append("─");
	}
	_GridBottom.append("┘");
}

bool BattleGrid::checkInputX(int x)
{
	if (x > -1 && x < 4)
	{
		return true;
	}

	return false;
}

bool BattleGrid::checkInputY(int y)
{
	if (y > -1 && y < 3)
	{
		return true;
	}

	return false;
}

void BattleGrid::DrawGrid()
{
	tbColor();
	for (int r = 0; r < _GridRowCount; r++)
	{
		for (int c = 0; c < _GridColumntCount; c++)
		{
			DrawBlock(c, r);
		}
	}
}

void BattleGrid::DrawBlock(int x, int y)
{
	if (!checkInputX(x)) return;// checkInputX is false
	if (!checkInputY(y)) return;//checkInputY is false

	GoToXY(_spawnX + x * _GridWidth, _spawnY + y * _GridHeight);
	std::cout << _GridTop <<std::flush;
	for (int i = 0; i < _GridHeight - 2; i++)
	{
		GoToXY(_spawnX + x * _GridWidth, _spawnY + y * _GridHeight + i + 1);
		std::cout << _GridMiddle;
	}
	GoToXY(_spawnX + x * _GridWidth, _spawnY + y * _GridHeight + _GridHeight - 1);
	std::cout << _GridBottom;
}

void BattleGrid::PaintBlocks(int x, int y, bool (*range)[3], Color background)
{
	tbColor(WHITE, background);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (range[i][j]) {
				DrawBlock(x + (j - 1), y + (i - 1));
			}
		}
	}
	tbColor();

	DrawCharacter();
    while (!_kbhit()){}
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}

void BattleGrid::SetCharacter(int x, int y, const char* filename)
{
    if (!checkInputX(x)) return;// checkInputX is false
    if (!checkInputY(y)) return;//checkInputY is false

    _IsSetedCharcter = true;

    _Character_BMP_Position[y][x].push_back(filename);
}

void BattleGrid::DrawCharacter()
{
	if (!_IsSetedCharcter) return; //_IsSetedCharcter is false

    ImagePrinter _ImagePrinter;

    int size;

	for (size_t y = 0; y < 3; y++)
	{
		for (size_t x = 0; x < 4; x++)
		{
			if (!_Character_BMP_Position[y][x].empty()) //is not empty
			{
                size = _Character_BMP_Position[y][x].size();
                for (size_t i = 0; i < size; i++)
                {
                    std::ifstream file(_Character_BMP_Position[y][x][i], std::ios::binary);
                    if (!file)
                    {
                        break;
                    }
                    else {
                        file.seekg(14);
                        BMPInfoHeader ih;
                        file.read(reinterpret_cast<char*>(&ih), sizeof(ih));

                        int halfwidth = (_GridWidth / size) + (_GridWidth * i);
                        int remain_space = halfwidth - ih.biWidth;
                        int spawnx = _spawnX + x * _GridWidth + (remain_space / 2);
                        int spawny = _spawnY + y * _GridHeight + 1;
                        _ImagePrinter.DrawImage(_Character_BMP_Position[y][x][i], spawnx, spawny);
                    }
                }
			}
		}
	}
}
