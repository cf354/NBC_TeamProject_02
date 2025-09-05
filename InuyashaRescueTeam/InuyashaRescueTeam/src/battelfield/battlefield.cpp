#include "battlefield/battlefield.h"
#include <iostream>

BattleField::BattleField()
{
    PlayerPositionX = 0;
    PlayerPositionY = 1;
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

void BattleField::field_move(int dirX, int dirY, int entityType)
{
    int currentX, currentY;
    int nextX, nextY;

    if (entityType == 1) { // 플레이어일 경우
        currentX = PlayerPositionX;
        currentY = PlayerPositionY;
    }
    else { // 적일 경우
        currentX = EnemyPositionX;
        currentY = EnemyPositionY;
    }

    nextX = currentX + dirX;
    nextY = currentY + dirY;

    if (battlegrid[nextY][nextX] != 0 || nextY > 2 || nextY < 0 || nextX > 3 || nextX < 0) {
        std::cout << "이동할 수 없습니다." << std::endl;
        return;
    }
    else {
        battlegrid[currentY][currentX] = 0;
        if (entityType == 1) {
            PlayerPositionX = nextX;
            PlayerPositionY = nextY;
        }
        else {
            EnemyPositionX = nextX;
            EnemyPositionY = nextY;
        }
        battlegrid[nextY][nextX] = entityType;
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