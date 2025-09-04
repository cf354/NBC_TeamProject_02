#include "C_Attack.hpp"

// 생성자 
C_Attack::C_Attack(std::string n, int C, int G, int A, const bool r[3][3]) : Card(n, C, G), ATK(A)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Range[i][j] = r[i][j];
        }
    }
}

// 소멸자 
C_Attack::~C_Attack()
{ }

// 멤버 함수 
int C_Attack::A_GetATK()
{
    return ATK;
}

// 2차원 배열 포인터 반환
bool(*C_Attack::A_GetRange())[3]
{
    return Range;
}