#include "C_Move.hpp"

// 생성자 
C_Move::C_Move(std::string n, int C, int G, int d, int dirx, int diry) : Card(n, C, G), distance(d), x(dirx), y(diry)
{ }

// 소멸자 
C_Move::~C_Move()
{ }

// 멤버 함수 
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