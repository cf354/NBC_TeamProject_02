#pragma once
#include "Singleton.h"
#include "Windows.h"

class TimeManager : public Singleton<TimeManager>
{
public:
    void Init();
    void Update();

    float DeltaTime();

private:
    LARGE_INTEGER frequency, last, curr;
    float totalTime = 0;
    float deltaTime = 0;
};

#define TIME ((TimeManager::GetInstance()))
