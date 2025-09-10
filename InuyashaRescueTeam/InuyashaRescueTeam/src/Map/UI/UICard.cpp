#include "Map/UI/UICard.h"
#include "Map/UI/UIText.h"
#include "Cards.h"
#include "Common/ConsolePrinter.h"
#include <codecvt>

UICard::UICard()
    : gridX(3), gridY(3), colorGrid(MColor::BLUE)
{
    SetSize(9, 8);
    grid = vector<vector<char>>(gridY, vector<char>(gridX, 0));

    textName = new UIText();
    textName->SetParent(this);
    textName->SetSize(Vector2D(size.x - 2, 3));
    textName->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(1, 1));
}

UICard::~UICard()
{
    delete textName;
    textName = nullptr;
}

void UICard::Update()
{
    UIBox::Update();
}

void UICard::Render()
{
    UIBox::Render();

    int startX = 2;
    int startY = 4;
    for (int i = 0; i < gridY; i++)
    {
        for (int j = 0; j < gridX; j++)
        {
            CONSOLE_PRINTER->SetData(worldPos.y + startY + i, worldPos.x + startX + j * 2, L'■', grid[i][j] == 0 ? MColor::WHITE : colorGrid);
        }
    }
}

void UICard::SetData(Card* card)
{
    ClearGrid();
    wstring_convert<codecvt_utf8_utf16<wchar_t>> conv;
    wstring wName = conv.from_bytes(card->C_GetName());
    textName->SetText(wName);
    if (C_Attack* cAtk = dynamic_cast<C_Attack*>(card))
    {
        const auto& range = cAtk->A_GetRange();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (range[i][j])
                {
                    UseGrid(i, j);
                }
            }
        }
    }
    else if (C_Guard* cGuard = dynamic_cast<C_Guard*>(card))
    {
        UseGrid(1, 1);
    }
    else if (C_Move* cMove = dynamic_cast<C_Move*>(card))
    {
        UseGrid(cMove->M_GetY() + 1, cMove->M_GetX() + 1);
    }
    else if (C_HealHP* cHHp = dynamic_cast<C_HealHP*>(card))
    {
        UseGrid(1, 1);
    }
    else if (C_HealStamina* cHStam = dynamic_cast<C_HealStamina*>(card))
    {
        UseGrid(1, 1);
    }
    else if (MasterCard* cMaster = dynamic_cast<MasterCard*>(card))
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                UseGrid(i, j);
            }
        }
    }
}

void UICard::ClearGrid()
{
    for (int i = 0; i < gridY; i++)
    {
        for (int j = 0; j < gridX; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void UICard::UseGrid(int y, int x)
{
    grid[y][x] = 1;
}

void UICard::SetColorGrid(MColor color)
{
    this->colorGrid = color;
}
