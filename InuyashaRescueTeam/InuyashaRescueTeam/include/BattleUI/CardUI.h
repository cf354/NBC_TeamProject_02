#pragma once
#include "UIWidget.h"
#include"Cards.h"
#include <vector>

class CardUI : public UIWidget
{
public:
	CardUI(int width, int height) :UIWidget(width, height) {
		_Count_Row = height / 7;
		_Count_Column = width / 14;
		_CanSeeCardMaxCount = _Count_Row * _Count_Column;
		SetGrid();
	}

	CardUI(int width, int height, int spawnX, int spawnY) :UIWidget(width, height, spawnX, spawnY) {
		_Count_Row = height / 7;
		_Count_Column = width / 14;
		_CanSeeCardMaxCount = _Count_Row * _Count_Column;
		SetGrid();
	}

private:
	int _Count_Row = 0;
	int _Count_Column = 0;
	int _CanSeeCardMaxCount = 0;

	std::string _GridTop;
	std::string _GridMiddle;
	std::string _GridBottom;

public:
	void virtual Draw() override;
	void SetGrid();
    void PrintCards(std::vector<std::shared_ptr<Card>> Cards);
	//void PrintCards(std::vector<Card*> Cards, int startIndex); // 화면에 출력되는 카드의 최대갯수를 이상을 출력하기 위해 만들었던 함수 입니다.
	void DrawClear();
	void DrawMoveCard(C_Move& Card, int x, int y); 
	void DrawAttackCard(C_Attack& Card, int x, int y);
    void DrawGuardCard(C_Guard& Card, int x, int y);
    std::shared_ptr<Card> ChoseCard(std::vector<std::shared_ptr<Card>> Cards);
	//void DrawGuardCard();
	//void DrawHealCard(Card& Card, int x, int y);
private:
    int GetConsoleCharWidth(wchar_t wc);
    void PrintCardName(const std::string& name, int x, int y);
};

