#include "C_Move.hpp"

// ������ 
C_Move::C_Move(std::string n, int C, int G, int d, int dirx, int diry) : Card(n, C, G), distance(d), x(dirx), y(diry)
{ }

// �Ҹ��� 
C_Move::~C_Move()
{ }

// ��� �Լ� 
int C_Move::M_GetX()
{
    return x;
}

int C_Move::M_GetY()
{
    return y;
}

int C_Move::M_GetDistance()
{
    return distance;
}