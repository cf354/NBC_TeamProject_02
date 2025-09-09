#pragma once
#include "IRenderer.h"
#include <string>
#include <map>
#include "Map/Render/TAnimation.h"

using namespace std;

class TAnimRenderer : public IRenderer
{
public:
	TAnimRenderer();

	void Update() override;
	void Render() override;

	void AddAnimation(TAnimation* anim);
	void SetCurrAnim(string animName);

private:
	map<string, TAnimation*> mapAnim;
    TAnimation* currAnim = nullptr;
};

