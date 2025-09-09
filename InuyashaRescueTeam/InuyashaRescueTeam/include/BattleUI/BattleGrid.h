#pragma once
#include "UIWidget.h"
#include <string>
#include <vector>
#include "ImagePrinter.h"

//플레이어위치, 플레이어 스킬 범위, 적 위치, 적 스킬 범위

class BattleGrid : public UIWidget
{
public :
	BattleGrid(int width, int height) : UIWidget(width, height) {
		_width = width < 12 ? 12 : width;
		_height = height < 9 ? 9 : height;
		_GridWidth = _width / 4;
		_GridHeight = _height / 3;
		SetGrid();
	}

	BattleGrid(int width, int height, int spawnX, int spawnY) : UIWidget(width, height, spawnX, spawnY) {
		_width = width < 12 ? 12 : width;
		_height = height < 9 ? 9 : height;
		_GridWidth = _width / 4;
		_GridHeight = _height / 3;
		SetGrid();
	}

private:
	int _GridWidth = 3;
	int _GridHeight = 3;

	int _GridRowCount= 3;
	int _GridColumntCount = 4;

	bool _IsSetedCharcter = false;
	std::vector<std::string> _Character_Position[3][4] = {};
    std::vector<const char*> _Character_BMP_Position[3][4] = {};
	int _Character_Postion_Color[3][4] = {};

	std::string _GridTop = "";
	std::string _GridMiddle = "";
	std::string _GridBottom = "";


public:
	virtual void Draw() override;	
	void PaintBlocks(int x,int y, bool (*range)[3], Color background);
	void SetCharacter(int x, int y, std::string string, Color font, Color background);
    void SetCharacter(int x, int y, const char* filename);

    void ReSet_Characters() {
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t k = 0; k < 4; k++)
            {
                _Character_BMP_Position[i][k].clear();
            }
        }

        _IsSetedCharcter = false;
    }

	void Reset_Character_Position() {
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				_Character_Position[i][k].clear();
			}
		}
		_IsSetedCharcter = false;
	}

private:  
	void SetGrid();
	bool checkInputX(int x);
	bool checkInputY(int y);
    void DrawGrid();
    void DrawCharacter();
    void DrawBlock(int x, int y);
};

