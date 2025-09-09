#include "Map/UI/UIBar.h"
#include "Common/ConsolePrinter.h"

UIBar::UIBar()
    : currValue(5), maxValue(100), colorBar(MColor::RED)
{
    SetSize(60, 1);
}

void UIBar::Render()
{
    int hpBarSizeX = size.x - textSize - 2;
    int nX = hpBarSizeX * currValue / maxValue;
    wstring str = text + to_wstring(currValue) + L'/' + to_wstring(maxValue);

    for (int i = 0; i < size.y; i++)
    {
        CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x, L' ');
        for (int j = 1; j <= textSize; j++)
        {
            bool textArea = (i == size.y / 2 && j < str.length());
            CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + j, textArea ? str[j] : L' ', MColor::WHITE);
        }
        for (int j = 1; j <= hpBarSizeX; j++)
        {
            CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + textSize + j, j < nX ? L'▬' : L' ', colorBar);
        }
        CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + size.x - 1, L' ');
    }

    UI::Render();
}

void UIBar::SetValue(int currValue, int maxValue)
{
    this->maxValue = maxValue;
    this->currValue = currValue;
}

void UIBar::SetTextArea(int size)
{
    this->textSize = size;
}

void UIBar::SetText(wstring text)
{
    this->text = text;
}

void UIBar::SetColorBar(MColor color)
{
    this->colorBar = color;
}
