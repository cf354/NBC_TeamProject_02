#include "Entity/Boss.h"
#include "Card/C_Move.h"
#include "Card/C_Attack.h"
#include "Card/C_Guard.h"
#include "Common/ConsolePrinter.h"
#include <random>

// 보스 덱 초기화 (Enemy::InitDeck() 오버라이드)
void Boss::InitDeck() {
    // Enemy의 공통 카드 추가 로직을 먼저 호출
    Enemy::InitDeck();

    // 보스 전용 카드 추가
    bool WideSlash[3][3] = { {true,false,true}, {false,true,false}, {true,false,true} };
    AddCard(std::make_shared<C_Attack>("B_WideSlash", 20, 0, 40, WideSlash));

    bool CrossSlash[3][3] = { {false,true,false}, {true,true,true}, {false,true,false} };
    AddCard(std::make_shared<C_Attack>("B_CrossSlash", 25, 0, 50, CrossSlash));

    // 보스 전용 카드 가중치 설정
    AddCardWeight("B_WideSlash", 3);
    AddCardWeight("B_CrossSlash", 4);

}

// 보스 전용 랜덤 카드 선택
std::shared_ptr<Card> Boss::GetRandomCard(int playerX, int playerY, int enemyX, int enemyY) {
    // 플레이어와 적 사이의 거리를 계산
    int distanceX = std::abs(playerX - enemyX);
    int distanceY = std::abs(playerY - enemyY);

    // 체력이 50% 이하일 때 페이즈 전환
    if (GetHP() < GetMAXHP() / 2 && phase == 1) {
        phase = 2;

        // 새로운 강력한 카드 추가
        bool RageAttack[3][3] = { {true,true,true}, {true,true,true}, {true,true,true} };
        AddCard(std::make_shared<C_Attack>("B_RageAttack", 40, 0, 80, RageAttack));
        AddCardWeight("B_RageAttack", 6);
    }

    // Boss 전용 가중치 조정 로직 추가
    if (distanceX <= 1 && distanceY <= 1) {
        cardWeights["B_WideSlash"] = 5;
        cardWeights["B_CrossSlash"] = 6;
        if (phase == 2) {
            cardWeights["B_RageAttack"] = 8;
        }
    }
    else {
        cardWeights["B_WideSlash"] = 3;
        cardWeights["B_CrossSlash"] = 4;
        if (phase == 2) {
            cardWeights["B_RageAttack"] = 6;
        }
    }

    // Enemy 클래스의 가중치 기반 랜덤 선택 로직을 직접 복사하여 사용
    int totalWeight = 0;
    for (const auto& pair : cardWeights) {
        totalWeight += pair.second;
    }

    if (totalWeight == 0) {
        return nullptr;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, totalWeight);
    int randomValue = distrib(gen);

    for (const auto& pair : cardWeights) {
        randomValue -= pair.second;
        if (randomValue <= 0) {
            for (const auto& card : deck) {
                if (card->C_GetName() == pair.first) {
                    return card;
                }
            }
        }
    }
    return nullptr;
}