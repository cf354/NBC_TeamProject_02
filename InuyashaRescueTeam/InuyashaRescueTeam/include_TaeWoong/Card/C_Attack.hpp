#pragma once
#include "Card.hpp"

class C_Attack : public Card
{
private:
    int ATK;
    bool Range[3][3];

public:
    // 생성자 및 소멸자 
    C_Attack(std::string n, int C, int G, int A, const bool r[3][3]);
    virtual ~C_Attack();

    // 멤버 함수 선언
    int A_GetATK();
    bool (*A_GetRange())[3];
};