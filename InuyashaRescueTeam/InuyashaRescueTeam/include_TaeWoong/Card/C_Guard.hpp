#pragma once
#include "Card.hpp"

class C_Guard : public Card
{
private:
    int DEF;

public:
    // 생성자 및 소멸자 선언
    C_Guard(std::string n, int C, int G, int D);
    virtual ~C_Guard();

    // 멤버 함수 선언
    int G_GetDEF();
};