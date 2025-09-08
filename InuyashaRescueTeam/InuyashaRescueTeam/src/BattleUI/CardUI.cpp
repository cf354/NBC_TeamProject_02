#include "BattleUI/CardUI.h"
#include <conio.h>
#include <locale>
#include <codecvt> 

void CardUI::Draw()
{
	GoToXY(_spawnX, _spawnY);
	std::cout << _GridTop;

	for (int i = 0; i < _height - 2; i++)
	{
		GoToXY(_spawnX, _spawnY + 1 + i);
		std::cout << _GridMiddle;
	}

	GoToXY(_spawnX, _spawnY + _height - 1);
	std::cout << _GridBottom;
}

void CardUI::SetGrid() {
	_GridTop.append("┌");
	for (int i = 0; i < _width - 2; i++)
	{
		_GridTop.append("─");
	}
	_GridTop.append("┐");

	_GridMiddle.append("│");
	for (int i = 0; i < _width - 2; i++)
	{
		_GridMiddle.append(" ");
	}
	_GridMiddle.append("│");

	_GridBottom.append("└");
	for (int i = 0; i < _width - 2; i++)
	{
		_GridBottom.append("─");
	}
	_GridBottom.append("┘");
}

void CardUI::PrintCards(std::vector<std::shared_ptr<Card>> Cards)
{
	int spawnX = _spawnX + 1;
	int spawnY = _spawnY + 1;
	GoToXY(spawnX, spawnY);
	
	int CardCount_Showed = 0;
    std::shared_ptr<Card> card;
	int drawX = 0;
	int drawY = 0;
	while (CardCount_Showed != _CanSeeCardMaxCount && CardCount_Showed != Cards.size())
	{
		drawX = (CardCount_Showed % _Count_Column) * 14;
		drawY = (CardCount_Showed / _Count_Column) * 7;

		card = Cards[CardCount_Showed];

        if (auto moveCard = dynamic_cast<C_Move*>(card.get()))
        {
            DrawMoveCard(*moveCard, spawnX + drawX, spawnY + drawY);
        }
        else if (auto defenseCard = dynamic_cast<C_Guard*>(card.get())) 
        {
            DrawGuardCard(*defenseCard, spawnX + drawX, spawnY + drawY);
        }
        else if (auto attackCard = dynamic_cast<C_Attack*>(card.get()))
        {
            DrawAttackCard(*attackCard, spawnX + drawX, spawnY + drawY);
        }
        else if (auto StaminaHealCard = dynamic_cast<C_HealStamina*>(card.get()))
        {
            DrawStaminaHealCard(*StaminaHealCard, spawnX + drawX, spawnY + drawY);
        }
        else if (auto HealCard = dynamic_cast<C_HealHP*>(card.get()))
        {
            DrawHealCard(*HealCard, spawnX + drawX, spawnY + drawY);
        }

		CardCount_Showed++;
	}
}

void CardUI::DrawClear()
{
	std::string s(_width, ' ');

	for (size_t i = 0; i < _height; i++)
	{
		GoToXY(_spawnX, _spawnY + i);
		std::cout << s;
	}
}

void CardUI::DrawMoveCard(C_Move& Card, int x, int y)
{
    PrintCardName(Card.C_GetName(), x, y);

    GoToXY(x, y + 3);
    std::cout << "DM : " << "0";
    GoToXY(x, y + 5);
    std::cout << "EN : " << Card.C_GetCost();

	GoToXY(x + 9, y + 3);
	std::cout << "■■■";
	GoToXY(x + 9, y + 4);
	std::cout << "■■■";
	GoToXY(x + 9, y + 5);
	std::cout << "■■■";
	
	int up = Card.M_GetY() * Card.M_GetDistance();
	int right = Card.M_GetX() * Card.M_GetDistance();

	int chX = 1 - (right / 2);
	int chY = 1 - (up / 2);
	GoToXY(x +  9 + chX, y + 3 + chY);
	tbColor(GREEN, BLACK);
	std::cout << "■";

	GoToXY(x + 9 + chX + right, y + 3 +chY + up);
	tbColor(BLUE, BLACK);
	std::cout << "■";

	tbColor();
}

void CardUI::DrawAttackCard(C_Attack& Card, int x, int y)
{
	bool (*range)[3] = Card.A_GetRange();

    PrintCardName(Card.C_GetName(), x, y);

    GoToXY(x, y + 3);
    std::cout << "DM : " << Card.A_GetATK();
    GoToXY(x, y + 5);
    std::cout << "EN : " << Card.C_GetCost();

    GoToXY(x + 9, y + 3);
    std::cout << "■■■";
    GoToXY(x + 9, y + 4);
    std::cout << "■■■";
    GoToXY(x + 9, y + 5);
    std::cout << "■■■";

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (range[i][j]) {
				GoToXY(x + 1 + (j - 1) + 9, y + 1 + (i - 1) + 3);
				tbColor(RED, BLACK);
				std::cout << "■";
			}
		}
	}

    tbColor(GREEN, BLACK);
    GoToXY(x + 1 + 9, y + 1 + 3);
    std::cout << "■";

	tbColor();
}

void CardUI::DrawGuardCard(C_Guard& Card, int x, int y)
{
    PrintCardName(Card.C_GetName(), x, y);

    GoToXY(x, y + 3);
    std::cout << "DM : " << Card.G_GetDEF();
    GoToXY(x, y + 5);
    std::cout << "EN : " << Card.C_GetCost();

    GoToXY(x + 9, y + 3);
    std::cout << "■■■";
    GoToXY(x + 9, y + 4);
    std::cout << "■■■";
    GoToXY(x + 9, y + 5);
    std::cout << "■■■";

	GoToXY(x + 1 + 9, y + 1 + 3);
	tbColor(GREEN, BLACK);
	std::cout << "■";

	tbColor();
}

void CardUI::DrawHealCard(C_HealHP& Card, int x, int y)
{
    PrintCardName(Card.C_GetName(), x, y);

    GoToXY(x, y + 3);
    std::cout << "DM : " << Card.GetHamount();
    GoToXY(x, y + 5);
    std::cout << "EN : " << Card.C_GetCost();

    GoToXY(x + 9, y + 3);
    std::cout << "■■■";
    GoToXY(x + 9, y + 4);
    std::cout << "■■■";
    GoToXY(x + 9, y + 5);
    std::cout << "■■■";

    GoToXY(x + 1 + 9, y + 1 + 3);
    tbColor(GREEN, BLACK);
    std::cout << "■";

    tbColor();
}

void CardUI::DrawStaminaHealCard(C_HealStamina& Card, int x, int y)
{
    PrintCardName(Card.C_GetName(), x, y);

    GoToXY(x, y + 3);
    std::cout << "DM : " << Card.GetHamount();
    GoToXY(x, y + 5);
    std::cout << "EN : " << Card.C_GetCost();

    GoToXY(x + 9, y + 3);
    std::cout << "■■■";
    GoToXY(x + 9, y + 4);
    std::cout << "■■■";
    GoToXY(x + 9, y + 5);
    std::cout << "■■■";

    GoToXY(x + 1 + 9, y + 1 + 3);
    tbColor(GREEN, BLACK);
    std::cout << "■";

    tbColor();
}

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

std::shared_ptr<Card> CardUI::ChoseCard(std::vector<std::shared_ptr<Card>> Cards)
{
    std::shared_ptr<Card> result = nullptr;
	int size = Cards.size();

	int x = 0;
	int y = 0;
	int before_x = 0;
	int before_y = 0;

	char input;

	GoToXY(_spawnX, _spawnY);
	std::cout << "카드 선택";


	GoToXY(_spawnX + 1, _spawnY + 7);
	std::cout << "▲ 선택 : 엔터";
	while (result == nullptr)
	{
		if (_kbhit()) {
			input = _getch();
			if (input == -32) {
				input = _getch();
				switch (input)
				{
				case LEFT: {
					if (x != 0) {
						before_x = x;
						before_y = y;
						x--;
					}
					break;
				}
				case RIGHT: {
					if (x != _Count_Column - 1 && (size - 1 >= (x + 1 + (_Count_Column * y)))) {
						before_x = x;
						before_y = y;
						x++;
					}
					break;
				}
				case UP: {
					if (y != 0) {
						before_x = x;
						before_y = y;
						y--;
					}
					break;
				}
				case DOWN: {
					if (y != _Count_Row  - 1 && (size - 1 >= (x + (_Count_Column * (y + 1))))) {
						before_x = x;
						before_y = y;
						y++;
					}
					break;
				}
				}
				GoToXY(_spawnX + before_x * 14 + 1, _spawnY + before_y * 7 + 7);
				std::cout << "              ";
				GoToXY(_spawnX + x * 14 + 1, _spawnY + y * 7 + 7);
				std::cout << "▲ 선택 : 엔터";
			}
			else if(input == 13){
				result = Cards[x + (_Count_Column * y)];
			}
		}
	}

	return result;
}

int CardUI::GetConsoleCharWidth(wchar_t wc) {
    // 유니코드 범위에 따라 대략적인 너비 반환 (전각 vs 반각)
    // CJK 통합 한자, 한글, 전각 기호 등은 일반적으로 2칸 폭
    if ((wc >= 0x1100 && wc <= 0x11FF) || // 한글 자모
        (wc >= 0x3000 && wc <= 0x9FFF) || // CJK 심볼 및 한자
        (wc >= 0xAC00 && wc <= 0xD7AF) || // 한글 음절
        (wc >= 0xFF00 && wc <= 0xFFEF)) { // 전각 문자 (Full-width forms)
        return 2;
    }

    return 1; // 영어, 숫자, 반각 문자 등은 1칸
}

void CardUI::PrintCardName(const std::string &name, int x, int y)
{
    static std::locale loc("");

    std::wstring wsname;
    auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
    wsname = std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(name);

    std::wcout.imbue(std::locale(""));

    int drawX = 0;
    int drawY = 0;
    for (size_t i = 0; i < wsname.size(); i++)
    {
        GoToXY(x + drawX, y + drawY);
        drawX += GetConsoleCharWidth(wsname[i]);
        if (drawX == 12) {
            drawY++;
            drawX = 0;
        }
        std::wcout << wsname[i];
    }
}