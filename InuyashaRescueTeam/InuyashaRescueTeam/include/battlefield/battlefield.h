#pragma once
#include <iostream>

class BattleField {//필드 적 플레이어 겹치는 거 구현
private:
    int battlegrid[3][4];
public:
    int PlayerPositionX;
    int PlayerPositionY;
    int EnemyPositionX;
    int EnemyPositionY;
    BattleField();

    void field_move(int dirX, int dirY);
    void field_print();
};