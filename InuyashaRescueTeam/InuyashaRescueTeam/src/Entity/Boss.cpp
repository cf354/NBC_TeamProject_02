#include "Entity/Boss.h"
#include "Card/C_Move.h"
#include "Card/C_Attack.h"
#include "Card/C_Guard.h"
#include "Common/ConsolePrinter.h"

// 보스 덱 초기화 (Enemy::InitDeck() 오버라이드)
void Boss::InitDeck() {
    // Enemy의 공통 카드 추가 로직을 먼저 호출
    Enemy::InitDeck();

    // 보스 전용 카드 추가
    bool WideSlash[3][3] = { {true,true,true}, {false,true,false}, {false,true,false} };
    AddCard(std::make_shared<C_Attack>("B_WideSlash", 20, 0, 40, WideSlash));

    bool CrossSlash[3][3] = { {true,false,true}, {false,true,false}, {true,false,true} };
    AddCard(std::make_shared<C_Attack>("B_CrossSlash", 25, 0, 50, CrossSlash));

    // 보스 전용 카드 가중치 설정
    AddCardWeight("B_WideSlash", 3);
    AddCardWeight("B_CrossSlash", 4);

}

// 보스 전용 랜덤 카드 선택
std::shared_ptr<Card> Boss::GetRandomCard(int playerX, int playerY, int enemyX, int enemyY) {
    // 체력이 50% 이하일 때 페이즈 전환
    if (GetHP() < GetMAXHP() / 2 && phase == 1) {
        phase = 2;

        // 새로운 강력한 카드 추가
        bool RageAttack[3][3] = { {true,true,true}, {true,true,true}, {true,true,true} };
        AddCard(std::make_shared<C_Attack>("B_RageAttack", 40, 0, 80, RageAttack));
        AddCardWeight("B_RageAttack", 6);
    }

    // 기본 Enemy의 가중치 기반 랜덤 선택을 그대로 활용
    return Enemy::GetRandomCard(playerX, playerY, enemyX, enemyY);
}