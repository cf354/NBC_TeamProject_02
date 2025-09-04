#include "C_Guard.hpp"

// 생성자 
C_Guard::C_Guard(std::string n, int C, int G, int D) : Card(n, C, G), DEF(D)
{ }

// 소멸자 
C_Guard::~C_Guard()
{ }

// 멤버 함수 구현
int C_Guard::G_GetDEF()
{
    return DEF;
}