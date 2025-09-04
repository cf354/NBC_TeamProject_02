#pragma once
#include "Card.h"
class C_Move :
	public Card
{

private:
	int distance = 1;
	int x = 0;
	int y = 0;
public:
	C_Move(std::string n, int C, int G, int d, int dirx, int diry) :Card(n, C, G), distance(d), x(dirx), y(diry) {}
	int M_GetX() {
		return x;
	}
	int M_GetY() {
		return y;
	}
	int M_GetDistance() {
		return distance;
	}
	virtual ~C_Move() {};


};

