#pragma once
#include <iostream>

class BattleField {
private:
	int battlegrid[3][4];
public:
	int PlayerPositionX;
	int PlayerPositionY;
	int EnemyPositionX;
	int EnemyPositionY;
	BattleField();

	void field_move(int dirX, int dirY, int entityType); // 매개변수 추가
	void field_print();
};