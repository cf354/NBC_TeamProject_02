#pragma once
#include "IRenderer.h"
#include "Map/MapTypes.h"
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace Map;

class Animation
{
public:
	Animation(string name, Vector2F pivot, Vector2D size);
	void Update();

	void Reset();
	void SetName(string name);
	void SetSprites(const vector<wstring>& sprites);
    /// <summary>
    /// 속도 1일 경우, 초당 한 프레임
    /// </summary>
    /// <param name="speed"></param>
    void SetSpeed(int speed = 16);

	string GetName();
	wstring GetSprite();
	Vector2F GetPivot();
	Vector2D GetSize();

private:
	string name;
	vector<wstring> sprites;
	Vector2F pivot;
	Vector2D size;
	int frame;
	int speed = 16;					// 1이면 1초에 한 프레임
	float timer;
};

class TAnimRenderer : public IRenderer
{
public:
	TAnimRenderer();

	void Update() override;
	void Render() override;

	void AddAnimation(Animation* anim);
	void SetCurrAnim(string animName);

private:
	map<string, Animation*> mapAnim;
	Animation* currAnim = nullptr;
};

