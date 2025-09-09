#include "Map/Camera.h"
#include "Map/Actor/Actor.h"
#include "Common/ConsolePrinter.h"

void Camera::Update()
{
    if (target != nullptr)
    {
        pos = target->GetPos();
        SetRect();
    }
}

void Camera::SetTarget(Actor* target)
{
    this->target = target;
}

const Vector2D& Camera::GetLT()
{
    return lt;
}

const Vector2D& Camera::GetRB()
{
    return rb;
}

void Camera::SetRect()
{
    lt.x = max(0, pos.x - DATA_WIDTH / 2);
    lt.y = max(0, pos.y - DATA_HEIGHT / 2);
    rb.x = lt.x + DATA_WIDTH - 1;
    rb.y = lt.y + DATA_HEIGHT - 1;
}
