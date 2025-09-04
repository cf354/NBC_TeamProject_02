#include "C_Attack.hpp"

// ������ 
C_Attack::C_Attack(std::string n, int C, int G, int A, const bool r[3][3]) : Card(n, C, G), ATK(A)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Range[i][j] = r[i][j];
        }
    }
}

// �Ҹ��� 
C_Attack::~C_Attack()
{ }

// ��� �Լ� 
int C_Attack::A_GetATK()
{
    return ATK;
}

// 2���� �迭 ������ ��ȯ
bool(*C_Attack::A_GetRange())[3]
{
    return Range;
}