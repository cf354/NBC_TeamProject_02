#include "Entity\Boss.h"
#include "Card/C_Move.h"
#include "Card/C_Attack.h"
#include "Card/C_Guard.h"
#include "Common/ConsolePrinter.h"

// ���� �� �ʱ�ȭ
void Boss::InitDeck() {
    // �̵� ī��
    AddCard(std::make_shared<C_Move>("B_MoveRight", 0, 0, 1, 1, 0));
    AddCard(std::make_shared<C_Move>("B_MoveLeft", 0, 0, 1, -1, 0));

    // �⺻ ���� ī��
    bool WideSlash[3][3] = { {true,true,true}, {false,true,false}, {false,true,false} };
    AddCard(std::make_shared<C_Attack>("B_WideSlash", 20, 0, 40, WideSlash));

    bool CrossSlash[3][3] = { {true,false,true}, {false,true,false}, {true,false,true} };
    AddCard(std::make_shared<C_Attack>("B_CrossSlash", 25, 0, 50, CrossSlash));

    // ����ġ ����
    AddCardWeight("B_MoveRight", 1);
    AddCardWeight("B_MoveLeft", 1);
    AddCardWeight("B_WideSlash", 3);
    AddCardWeight("B_CrossSlash", 4);
}

// ���� ���� ���� ī�� ����
std::shared_ptr<Card> Boss::GetRandomCard(int playerX, int playerY, int enemyX, int enemyY) {
    // ü���� 50% ������ �� ������ ��ȯ
    if (GetHP() < GetHP() / 2 && phase == 1) {   // ü�� �������°� ���� ���� ����
        phase = 2;

        // ���ο� ������ ī�� �߰�
        bool RageAttack[3][3] = { {true,true,true}, {true,true,true}, {true,true,true} };
        AddCard(std::make_shared<C_Attack>("B_RageAttack", 40, 0, 80, RageAttack));
        AddCardWeight("B_RageAttack", 6);
    }

    // �⺻ Enemy�� ����ġ ��� ���� ������ �״�� Ȱ��
    return Enemy::GetRandomCard(playerX, playerY, enemyX, enemyY);
}
