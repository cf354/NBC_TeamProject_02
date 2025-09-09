#include "Map/Component/TAnimRenderer.h"
#include "Common/ConsolePrinter.h"
#include "Map/Actor/Actor.h"
#include "Map/Managers/SceneManager.h"
#include "Map/Camera.h"
#include "Common/TimeManager.h"

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
    TSprite sprite = currAnim->GetSprite();
	Vector2D size = sprite.GetSize();
    wstring data = sprite.GetData();
    WORD attribute = sprite.GetAttribute();
	pos.y -= (size.y - 1) * pivot.y;
	pos.x -= (size.x - 1) * pivot.x;
	int idx, x, y;
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			idx = i * size.x + j;
			if (data[idx] == RENDER_ALPHA)
				continue;
			
			y = pos.y + i;
			x = pos.x + j;
			if (y < lt.y || y > rb.y || x < lt.x || x > rb.x)
				continue;

			CONSOLE_PRINTER->SetData(y - lt.y, x - lt.x, data[idx], attribute);
		}
	}
}

void TAnimRenderer::AddAnimation(TAnimation* anim)
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
