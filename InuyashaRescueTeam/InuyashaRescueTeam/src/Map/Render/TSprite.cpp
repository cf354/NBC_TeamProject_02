#include "Map/Render/TSprite.h"

TSprite::TSprite()
    : size(), data(L""), color(MColor::WHITE)
{
}

TSprite::TSprite(Vector2D size, wstring data, MColor color)
    : size(size), data(data), color(color)
{
}

Vector2D TSprite::GetSize()
{
    return size;
}

wstring TSprite::GetData()
{
    return data;
}

MColor TSprite::GetColor()
{
    return color;
}
