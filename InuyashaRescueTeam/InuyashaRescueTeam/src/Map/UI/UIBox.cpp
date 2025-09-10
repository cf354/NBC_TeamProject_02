#include "Map/UI/UIBox.h"
#include "Common/ConsolePrinter.h"

void UIBox::Render()
{
    if (!isActive)
        return;

    int maxX = size.x - 1;
    int maxY = size.y - 1;
    // 네 꼭짓점
    CONSOLE_PRINTER->SetData(worldPos.y, worldPos.x, L'┌');
    CONSOLE_PRINTER->SetData(worldPos.y, worldPos.x + maxX, L'┐');
    CONSOLE_PRINTER->SetData(worldPos.y + maxY, worldPos.x, L'└');
    CONSOLE_PRINTER->SetData(worldPos.y + maxY, worldPos.x + maxX, L'┘');
    // 세로변
    for (int i = 1; i < maxY; i++)
    {
        CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x, L'│');
        CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + maxX, L'│');
    }
    // 가로변
    for (int i = 1; i < maxX; i++)
    {
        CONSOLE_PRINTER->SetData(worldPos.y, worldPos.x + i, L'─' );
        CONSOLE_PRINTER->SetData(worldPos.y + maxY, worldPos.x + i, L'─');
    }
    // 내부 채우기
    for (int i = 1; i < maxY; i++)
    {
        for (int j = 1; j < maxX; j++)
        {
            CONSOLE_PRINTER->SetData(worldPos.y + i, worldPos.x + j, L' ');
        }
    }

    UI::Render();
}
