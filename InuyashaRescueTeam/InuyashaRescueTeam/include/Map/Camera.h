#pragma once
#include "Map/MapTypes.h"

class Actor;

using namespace Map;

class Camera
{
public:
    void Update();
    void SetTarget(Actor* target);

    const Vector2D& GetLT();
    const Vector2D& GetRB();

private:
    void SetRect();

private:
    Actor* target;

    Vector2D pos;
    Vector2D lt;			// 카메라 영역 좌상단
    Vector2D rb;			// 카메라 영영 우하단
};

