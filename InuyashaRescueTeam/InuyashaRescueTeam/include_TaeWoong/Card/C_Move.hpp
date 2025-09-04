#pragma once
#include "Card.hpp"

class C_Move : public Card
{
private:
    int distance;
    int x;
    int y;

public:
    // ������ �� �Ҹ��� ����
    C_Move(std::string n, int C, int G, int d, int dirx, int diry);
    virtual ~C_Move();

    // ��� �Լ� ����
    int M_GetX();
    int M_GetY();
    int M_GetDistance();
};