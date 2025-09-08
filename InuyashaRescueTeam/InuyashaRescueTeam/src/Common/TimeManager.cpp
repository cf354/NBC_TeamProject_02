#include "Common/TimeManager.h"

void TimeManager::Init()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&last);
}

void TimeManager::Update()
{
    QueryPerformanceCounter(&curr);
    deltaTime = (curr.QuadPart - last.QuadPart) / (float)frequency.QuadPart;
    totalTime += deltaTime;
    last = curr;
}

float TimeManager::DeltaTime()
{
    return deltaTime;
}
