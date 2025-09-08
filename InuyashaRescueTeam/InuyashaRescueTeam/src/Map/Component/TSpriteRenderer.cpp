#include "Map/Component/TSpriteRenderer.h"
#include "Common/ConsolePrinter.h"
#include "Map/Actor/Actor.h"
#include "Map/Managers/SceneManager.h"
#include "Map/Camera.h"

TSpriteRenderer::TSpriteRenderer()
	: size(), sprite(L"")
{
}

void TSpriteRenderer::Update()
{
}

void TSpriteRenderer::Render()
{
	Camera* camera = SCENE_MANAGER->GetCurrentScene()->GetCamera();
	if (camera == nullptr)
		return;
	Vector2D lt = camera->GetLT();
	Vector2D rb = camera->GetRB();
	Vector2D pos = owner->GetPos();
	pos.y -= (size.y - 1) * pivot.y;
	pos.x -= (size.x - 1) * pivot.x;
	int idx, x, y;
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

void TSpriteRenderer::SetSprite(Vector2F pivot, Vector2D size, wstring sprite)
{
	this->pivot = pivot;
	this->size = size;
	this->sprite = sprite;
}
