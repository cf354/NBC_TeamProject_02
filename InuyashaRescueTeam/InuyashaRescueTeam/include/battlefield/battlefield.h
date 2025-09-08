#pragma once
#include <iostream>

class BattleField {

public:
    int battlegrid[3][4];
	int PlayerPositionX;
	int PlayerPositionY;
	int EnemyPositionX;
	int EnemyPositionY;
    

	void field_move(int dirX, int dirY, int entityType); // 매개변수 추가
	void field_print();
    bool MoveCheck(int dirX,int dirY,int entityType);
};