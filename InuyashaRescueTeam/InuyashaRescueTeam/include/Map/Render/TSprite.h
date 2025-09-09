#pragma once
#include <string>
#include <Windows.h>
#include "Map/MapTypes.h"

using namespace std;
using namespace Map;

class TSprite
{
public:
    TSprite();
    TSprite(Vector2D size, wstring data, WORD attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    Vector2D GetSize();
    wstring GetData();
    WORD GetAttribute();

private:
    Vector2D size;
    wstring data;
    WORD attribute;
};

