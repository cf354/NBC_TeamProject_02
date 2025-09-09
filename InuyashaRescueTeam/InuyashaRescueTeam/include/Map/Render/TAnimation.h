#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "Map/MapTypes.h"
#include "Map/Render/TSprite.h"

using namespace std;
using namespace Map;

class TAnimation
{
public:
    TAnimation(string name, Vector2F pivot);
    void Update();

    void Reset();
    void SetName(string name);
    void SetSprites(const vector<TSprite>& sprites);
    /// <summary>
    /// 속도 1일 경우, 초당 한 프레임
    /// </summary>
    /// <param name="speed"></param>
    void SetSpeed(int speed = 16);

    string GetName();
    TSprite GetSprite();
    Vector2F GetPivot();

private:
    string name;
    vector<TSprite> sprites;
    Vector2F pivot;
    int frame;
    int speed = 16;					// 1이면 1초에 한 프레임
    float timer;
};

