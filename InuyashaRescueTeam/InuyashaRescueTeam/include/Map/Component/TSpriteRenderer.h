#pragma once
#include "IRenderer.h"
#include "Map/Render/TSprite.h"

using namespace Map;

class TSpriteRenderer : public IRenderer
{
public:
	TSpriteRenderer();

	void Update() override;
	void Render() override;

	void SetSprite(Vector2F pivot, TSprite sprite);

private:
	Vector2F pivot;
    TSprite sprite;
};

