#pragma once
#include "IRenderer.h"
#include "Map/MapTypes.h"
#include <string>

using namespace std;
using namespace Map;

class TSpriteRenderer : public IRenderer
{
public:
	TSpriteRenderer();

	void Update() override;
	void Render() override;

	void SetSprite(Vector2F pivot, Vector2D size, wstring sprite);

private:
	Vector2F pivot;
	Vector2D size;
	wstring sprite;
};

