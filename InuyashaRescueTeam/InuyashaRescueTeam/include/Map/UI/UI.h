#pragma once
#include <string>
#include <vector>
#include "Map/MapTypes.h"

using namespace std;
using namespace Map;

enum class Anchor
{
	LT, CT, RT,
	LM, CM, RM,
	LB, CB, RB
};

/// <summary>
/// UI Object 클래스
/// UI Element를 붙여서 써야 함 -> 안 붙이면 그냥 텅 빈 오브젝트임
/// 앵커만 바꾸거나 피봇만 바꾸면, WorldPos는 냅두고 pos(상대 위치)를 계속 바꿔줘야 해서, 그냥 앵커나 피봇만 바꾸는 함수는 안 만듬
/// </summary>
class UI
{
protected:
	Vector2D GetAnchorPosition();							// 내 앵커를 기준으로 부모에게서 기준점 좌표 가져오기
    void Reposition();                                      // 부모 위치 바뀌었을 때, 자식들 순회하면서 재조정

public:
	virtual ~UI();
	virtual void Update();
    virtual void Render();

	void SetParent(UI* parent);
	void SetPosition(Anchor anchor, Vector2F pivot, Vector2D pos);							// anchor, pivot 고려한 상대 좌표
	void SetPosition(Anchor anchor, Vector2F pivot, int x, int y);							// anchor, pivot 고려한 상대 좌표
	virtual void SetSize(Vector2D size);
	virtual void SetSize(int x, int y);

	Vector2D GetPosition(bool isWorldPosition = false);
	Vector2D GetSize();

    vector<UI*> GetAllChildren();

protected:
	string name;
	Anchor anchor;
	Vector2F pivot;				// 0 ~ 1
	Vector2D size;
	Vector2D relativePos;		// anchor, pivot 고려한 상대위치
	Vector2D worldPos;			// 절대 위치 좌상단
	UI* parent;
	vector<UI*> children;
};
