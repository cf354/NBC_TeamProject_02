#pragma once
#include <iostream>

class BattleField {//�ʵ� �� �÷��̾� ��ġ�� �� ����
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