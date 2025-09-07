#include "BattleUI/UIWidget.h"

void UIWidget::GoToXY(int x, int y)
{
	COORD pos = { x,y }; //x, y 좌표 설정
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UIWidget::tbColor(unsigned short textColor, unsigned short backColor) {
	int color = textColor + backColor * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
