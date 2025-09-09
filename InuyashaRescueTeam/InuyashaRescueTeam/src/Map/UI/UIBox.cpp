#include "Map/UI/UIBox.h"
#include "Common/ConsolePrinter.h"

void UIBox::Render()
{
    int maxX = size.x - 1;
    int maxY = size.y - 1;
    CONSOLE_PRINTER->SetData(worldPos.y, worldPos.x, L'┌');
    CONSOLE_PRINTER->SetData(worldPos.y, worldPos.x + maxX, L'┐');
    CONSOLE_PRINTER->SetData(worldPos.y + maxY, worldPos.x, L'└');
    CONSOLE_PRINTER->SetData(worldPos.y + maxY, worldPos.x + maxX, L'┘');
    for (int i = 1; i < maxY; i++)
    {
        CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x, L'│');
        CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + maxX, L'│');
    }
    for (int i = 1; i < maxX; i++)
    {
        CONSOLE_PRINTER->SetData(worldPos.y, worldPos.x + i, L'─' );
        CONSOLE_PRINTER->SetData(worldPos.y + maxY, worldPos.x + i, L'─');
    }

    UI::Render();
}
