#include "Map/UI/UI.h"
#include "Common/ConsolePrinter.h"

UI::~UI()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}

void UI::Update()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update();
	}
}

void UI::Render()
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->Render();
    }
}

void UI::SetPosition(Anchor anchor, Vector2F pivot, Vector2D pos)
{
	this->anchor = anchor;
	relativePos = pos;
	Vector2D anchorPos = GetAnchorPosition();
	worldPos = { anchorPos.x - (int)(size.x * pivot.x) + pos.x, anchorPos.y - (int)(size.y * pivot.y) + pos.y };
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->Reposition();
    }
}

void UI::SetPosition(Anchor anchor, Vector2F pivot, int x, int y)
{
	SetPosition(anchor, pivot, { x, y });
}

void UI::SetSize(Vector2D size)
{
	this->size = size;
}

void UI::SetSize(int x, int y)
{
	SetSize({ x, y });
}

Vector2D UI::GetPosition(bool isWorldPosition)
{
	return isWorldPosition ? worldPos : relativePos;
}

Vector2D UI::GetSize()
{
	return size;
}

vector<UI*> UI::GetAllChildren()
{
    vector<UI*> result;
    for (int i = 0; i < children.size(); i++)
    {
        vector<UI*> elements = children[i]->GetAllChildren();
        for (int j = 0; j < elements.size(); j++)
        {
            result.push_back(elements[j]);
        }
        result.push_back(children[i]);
    }
    return result;
}

void UI::SetParent(UI* parent)
{
	this->parent = parent;
	parent->children.push_back(this);
}

Vector2D UI::GetAnchorPosition()
{
	Vector2D pos, size;
	// 캔버스 역할
	// 부모가 없는 UI의 경우, 화면을 꽉 채우는 캔버스에 있다고 가정하고 위치 조정
	if (parent == nullptr)
	{
		pos = { 0, 0 };
		size = { DATA_WIDTH - 1, DATA_HEIGHT - 1 };
	}
	else
	{
		pos = parent->GetPosition(true);
		size = parent->GetSize();
	}
	return { pos.x + (int)(size.x * 0.5f * ((int)anchor % 3)), pos.y + (int)(size.y * 0.5f * ((int)anchor / 3)) };
}

void UI::Reposition()
{
    SetPosition(anchor, pivot, relativePos);
}
