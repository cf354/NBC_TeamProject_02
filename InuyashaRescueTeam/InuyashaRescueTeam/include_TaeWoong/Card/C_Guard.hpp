#pragma once
#include "Card.hpp"

class C_Guard : public Card
{
private:
    int DEF;

public:
    // ������ �� �Ҹ��� ����
    C_Guard(std::string n, int C, int G, int D);
    virtual ~C_Guard();

    // ��� �Լ� ����
    int G_GetDEF();
};