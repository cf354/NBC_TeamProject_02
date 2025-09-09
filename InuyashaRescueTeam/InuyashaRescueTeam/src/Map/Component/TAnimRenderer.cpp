#include "Map/Component/TAnimRenderer.h"
#include "Common/ConsolePrinter.h"
#include "Map/Actor/Actor.h"
#include "Map/Managers/SceneManager.h"
#include "Map/Camera.h"
#include "Common/TimeManager.h"

Animation::Animation(string name, Vector2F pivot, Vector2D size)
	: name(name), pivot(pivot), size(size), frame(0), timer(0)
{
}

void Animation::Update()
{
	timer += TIME->DeltaTime() * speed;
	if (timer >= 1)
	{
		frame = ++frame >= sprites.size() ? 0 : frame;
		timer = 0;
	}
}

void Animation::Reset()
{
	frame = 0;
}

void Animation::SetName(string name)
{
	this->name = name;
}

void Animation::SetSprites(const vector<wstring>& sprites)
{
	this->sprites = sprites;
}

void Animation::SetSpeed(int speed)
{
    this->speed = speed;
}

string Animation::GetName()
{
	return name;
}

wstring Animation::GetSprite()
{
	return sprites[frame];
}

Vector2F Animation::GetPivot()
{
	return pivot;
}

Vector2D Animation::GetSize()
{
	return size;
}

TAnimRenderer::TAnimRenderer()
	: mapAnim()
{
}

void TAnimRenderer::Update()
{
	if (currAnim != nullptr)
	{
		currAnim->Update();
	}
}

void TAnimRenderer::Render()
{
	if (currAnim == nullptr)
		return;

	Camera* camera = SCENE_MANAGER->GetCurrentScene()->GetCamera();
	if (camera == nullptr)
		return;
	Vector2D lt = camera->GetLT();
	Vector2D rb = camera->GetRB();
	Vector2D pos = owner->GetPos();
	Vector2F pivot = currAnim->GetPivot();
	Vector2D size = currAnim->GetSize();
	pos.y -= (size.y - 1) * pivot.y;
	pos.x -= (size.x - 1) * pivot.x;
	int idx, x, y;
	wstring sprite = currAnim->GetSprite();
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			idx = i * size.x + j;
			if (sprite[idx] == RENDER_ALPHA)
				continue;
			
			y = pos.y + i;
			x = pos.x + j;
			if (y < lt.y || y > rb.y || x < lt.x || x > rb.x)
				continue;

			CONSOLE_PRINTER->SetData(y - lt.y, x - lt.x, sprite[idx]);
		}
	}
}

void TAnimRenderer::AddAnimation(Animation* anim)
{
	this->mapAnim.insert(make_pair(anim->GetName(), anim));
}

void TAnimRenderer::SetCurrAnim(string animName)
{
	if ((currAnim != nullptr && animName == currAnim->GetName()) || 
		 mapAnim.find(animName) == mapAnim.end())
		return;

	currAnim = mapAnim[animName];
	currAnim->Reset();
}
