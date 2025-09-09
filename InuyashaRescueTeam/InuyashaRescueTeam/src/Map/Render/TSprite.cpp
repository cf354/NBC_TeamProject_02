#include "Map/Render/TSprite.h"

TSprite::TSprite()
    : size(), data(L""), attribute(0)
{
}

TSprite::TSprite(Vector2D size, wstring data, WORD attribute)
    : size(size), data(data), attribute(attribute)
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

WORD TSprite::GetAttribute()
{
    return attribute;
}
