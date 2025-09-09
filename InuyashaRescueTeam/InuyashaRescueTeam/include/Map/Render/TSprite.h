#pragma once
#include <string>
#include "Map/MapTypes.h"

using namespace std;
using namespace Map;

class TSprite
{
public:
    TSprite();
    TSprite(Vector2D size, wstring data, MColor color = MColor::WHITE);
    
    Vector2D GetSize();
    wstring GetData();
    MColor GetColor();

private:
    Vector2D size;
    wstring data;
    MColor color;
};

