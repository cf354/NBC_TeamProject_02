#include "C_Guard.hpp"

// ������ 
C_Guard::C_Guard(std::string n, int C, int G, int D) : Card(n, C, G), DEF(D)
{ }

// �Ҹ��� 
C_Guard::~C_Guard()
{ }

// ��� �Լ� ����
int C_Guard::G_GetDEF()
{
    return DEF;
}