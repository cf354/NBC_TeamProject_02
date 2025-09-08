#include "battlefield/battlefield.h"



void BattleField::field_move(int dirX, int dirY, int entityType)
{
	int* currentX = (entityType == 1) ? &PlayerPositionX : &EnemyPositionX;
	int* currentY = (entityType == 1) ? &PlayerPositionY : &EnemyPositionY;

	int NextX = *currentX + dirX;
	int NextY = *currentY + dirY;


	if (NextY > 2 || NextY < 0 || NextX > 3 || NextX < 0) {
		//(entityType == 1) ? std::cout << "플레이어가 " : std::cout << "적이 ";
		//std::cout << "이동할 수 없습니다." << std::endl;
		return;
	}

	if (battlegrid[*currentY][*currentX] == 3) {
		battlegrid[*currentY][*currentX] = (entityType == 1) ? 2 : 1;
	}
	else {
		battlegrid[*currentY][*currentX] = 0;
	}
	*currentX = NextX;
	*currentY = NextY;
	if (battlegrid[*currentY][*currentX] != 0) {
		battlegrid[*currentY][*currentX] = 3;
	}
	else {
		battlegrid[*currentY][*currentX] = entityType;
	}
	//(entityType == 1) ? std::cout << "플레이어가 " : std::cout << "적이 ";
	//std::cout << "이동 성공" << std::endl;
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

bool BattleField::MoveCheck(int dirX, int dirY, int entityType)
{
    int* currentX = (entityType == 1) ? &PlayerPositionX : &EnemyPositionX;
    int* currentY = (entityType == 1) ? &PlayerPositionY : &EnemyPositionY;

    int NextX = *currentX + dirX;
    int NextY = *currentY + dirY;


    if (NextY > 2 || NextY < 0 || NextX > 3 || NextX < 0) {
        //(entityType == 1) ? std::cout << "플레이어가 " : std::cout << "적이 ";
        //std::cout << "이동할 수 없습니다." << std::endl;
        return false;
    }
    else {
        return true;
    }
}
