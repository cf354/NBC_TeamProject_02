#include "Map/Actor/APlayer.h"
#include "Map/Component/TAnimRenderer.h"
#include "Map/Component/Collider.h"
#include "Common/ConsolePrinter.h"
#include "Common/TimeManager.h"
#include "GameManager/GameManager.h"
#include "Map/Managers/MapManager.h"

APlayer::APlayer()
	: lastPos()
{
	AddInputMove();
}

APlayer::~APlayer()
{
}

void APlayer::Update()
{
	if (!isMovableX)
	{
		moveTimer.x += TIME->DeltaTime() * moveSpeed.x;
		if (moveTimer.x >= 1.0f)
		{
			isMovableX = true;
			moveTimer.x = 0.0f;
		}
	}
	if (!isMovableY)
	{
		moveTimer.y += TIME->DeltaTime() * moveSpeed.y;
		if (moveTimer.y >= 1.0f)
		{
			isMovableY = true;
			moveTimer.y = 0.0f;
		}
	}

	// 움직이고 Actor::Update()로 충돌체의 위치가 현재 위치로 업데이트 된 후에, 다른 Collider랑 충돌을 감지해서 부딪혔으면 원상복구 해야 함
	Move();
	Actor::Update();

	TAnimRenderer* animRenderer = GetComponent<TAnimRenderer>();
	animRenderer->SetCurrAnim(movePos.x != 0 ? "WalkSide" : (movePos.y != 0 ? "WalkUpDown" : "Idle"));

	// 충돌이 있으면, 다시 전 위치로 복귀
	Collider* collider = GetComponent<Collider>();
	if (collider != nullptr && !collider->DetectCollision().empty())
	{
		SetPos(lastPos);
	}

	lastPos = pos;
	movePos = Vector2D(0, 0);
}

void APlayer::MoveX(int x)
{
	movePos.x = x;
}

void APlayer::MoveY(int y)
{
	movePos.y = y;
}

void APlayer::Move()
{
    MoveX(GetAsyncKeyState(VK_LEFT) & 0x8000 ? -1 : GetAsyncKeyState(VK_RIGHT) & 0x8000 ? 1 : 0);
    MoveY(GetAsyncKeyState(VK_UP) & 0x8000 ? -1 : GetAsyncKeyState(VK_DOWN) & 0x8000 ? 1 : 0);
	if ((!isMovableX || movePos.x == 0) && (!isMovableY || movePos.y == 0))
		return;

    // x축 이동과 y축 이동 중 하나만 가능하게 변경
	if (isMovableX && movePos.x != 0)
	{
		pos.x = max(pos.x + movePos.x, 0);
		isMovableX = false;
	}
	else
	{
		pos.y = max(pos.y + movePos.y, 0);
		isMovableY = false;
	}
    MAP_MANAGER->CheckBattle();
}

void APlayer::AddInputMove()
{
    /*
    INPUT_MANAGER->AddEventKeyPressed(KeyCode::Up, [this]() { MoveY(-1); });
	INPUT_MANAGER->AddEventKeyPressed(KeyCode::Down, [this]() { MoveY(1); });
	INPUT_MANAGER->AddEventKeyPressed(KeyCode::Left, [this]() { MoveX(-1); });
	INPUT_MANAGER->AddEventKeyPressed(KeyCode::Right, [this]() { MoveX(1); });*/
}
