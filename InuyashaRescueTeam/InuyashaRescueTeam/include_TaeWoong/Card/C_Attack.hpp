#pragma once
#include "Card.hpp"

class C_Attack : public Card
{
private:
    int ATK;
    bool Range[3][3];

public:
    // ������ �� �Ҹ��� 
    C_Attack(std::string n, int C, int G, int A, const bool r[3][3]);
    virtual ~C_Attack();

    // ��� �Լ� ����
    int A_GetATK();
    bool (*A_GetRange())[3];
};