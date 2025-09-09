#pragma once
#include "Actor.h"

class Collider;

class APlayer : public Actor
{
public:
    APlayer();
	~APlayer();

	void Update() override;
	void MoveX(int x);
	void MoveY(int y);
	void Move();

	void AddInputMove();

private:
	Vector2D lastPos;
	Vector2D movePos;
	Vector2D direction = Vector2D(1, 0);
	Vector2D moveSpeed = Vector2D(50, 30);							// 텍스트 기반이기 때문에, 위치를 소수점 단위로 움직일 수 없음. 움직임은 1로 제한하고, 움직임 사이에 delay를 두는 방식으로 이동
	Vector2F moveTimer = Vector2F(0.0f, 0.0f);
	bool isMovableX = false, isMovableY = false;
};
