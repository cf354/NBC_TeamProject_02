#include "Map/Render/TAnimation.h"
#include "Common/TimeManager.h"

TAnimation::TAnimation(string name, Vector2F pivot)
    : name(name), pivot(pivot), frame(0), timer(0)
{
}

void TAnimation::Update()
{
    timer += TIME->DeltaTime() * speed;
    if (timer >= 1)
    {
        frame = ++frame >= sprites.size() ? 0 : frame;
        timer = 0;
    }
}

void TAnimation::Reset()
{
    frame = 0;
}

void TAnimation::SetName(string name)
{
    this->name = name;
}

void TAnimation::SetSprites(const vector<TSprite>& sprites)
{
    this->sprites = sprites;
}

void TAnimation::SetSpeed(int speed)
{
    this->speed = speed;
}

string TAnimation::GetName()
{
    return name;
}

TSprite TAnimation::GetSprite()
{
    return sprites[frame];
}

Vector2F TAnimation::GetPivot()
{
    return pivot;
}