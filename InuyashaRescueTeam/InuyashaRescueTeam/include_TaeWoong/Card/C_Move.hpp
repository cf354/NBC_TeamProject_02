#pragma once
#include "Card.hpp"

class C_Move : public Card
{
private:
    int distance;
    int x;
    int y;

public:
    // 생성자 및 소멸자 선언
    C_Move(std::string n, int C, int G, int d, int dirx, int diry);
    virtual ~C_Move();

    // 멤버 함수 선언
    int M_GetX();
    int M_GetY();
    int M_GetDistance();
};