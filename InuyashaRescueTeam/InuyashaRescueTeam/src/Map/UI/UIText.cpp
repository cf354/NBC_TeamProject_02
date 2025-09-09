#include "Map/UI/UIText.h"
#include "Common/ConsolePrinter.h"

void UIText::Render()
{
	int idx = 0;
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + j, idx >= text.size() ? ' ' : text[idx++], color);
		}
	}

    UI::Render();
}

void UIText::SetText(wstring text)
{
	this->text = text;
}

void UIText::SetColor(MColor color)
{
    this->color = color;
}
