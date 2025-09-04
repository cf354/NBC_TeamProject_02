#include "battlefield\battlefield.h"

BattleField::BattleField()
{
	PlayerPositionX = 0;
	PlayerPositionY = 2;
	EnemyPositionX = 3;
	EnemyPositionY = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			battlegrid[i][j] = 0;
		}
	}
	battlegrid[PlayerPositionY][PlayerPositionX] = 1;
	battlegrid[EnemyPositionY][EnemyPositionX] = 2;
}

void BattleField::field_move(int dirX, int dirY)
{
	int NextX = PlayerPositionX + dirX;
	int NextY = PlayerPositionY + dirY;

	if (battlegrid[NextY][NextX] != 0 || NextY > 2 || NextY < 0 || NextX>3 || NextX < 0) {
		std::cout << "이동할 수 없습니다." << std::endl;
		return;
	}
	else {
		battlegrid[PlayerPositionY][PlayerPositionX] = 0;
		PlayerPositionX = NextX;
		PlayerPositionY = NextY;
		battlegrid[PlayerPositionY][PlayerPositionX] = 1;
		std::cout << "이동 성공" << std::endl;
	}

}

void BattleField::field_print()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << battlegrid[i][j];
		}
		std::cout << std::endl;
	}
}

