#include "Map/UI/Text.h"
#include "Common/ConsolePrinter.h"

void Text::Update()
{
    UI::Update();
}

void Text::Render()
{
	int idx = 0;
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			if (idx >= text.length())
			{
				return;
			}
			CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + j, text[idx++], color);
		}
	}
}

void Text::SetText(wstring text, MColor color)
{
	this->text = text;
    this->color = color;
}
