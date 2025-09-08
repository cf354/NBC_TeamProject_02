#include "Entity/Enemy.h"
#include "Card/C_Attack.h"
#include "Card/C_Move.h"
#include <random>

std::string Enemy::GetName()
{
    return Name;
}

// 몬스터 타입에 따라 덱을 초기화하는 함수
void Enemy::InitDeck() {
    // 몬스터 공통 카드: 이동 카드
    AddCard(std::make_shared<C_Move>("E_MoveRight", 0, 0, 1, 1, 0));
    AddCard(std::make_shared<C_Move>("E_MoveLeft", 0, 0, 1, -1, 0));
    AddCard(std::make_shared<C_Move>("E_MoveUp", 0, 0, 1, 0, -1));
    AddCard(std::make_shared<C_Move>("E_MoveDown", 0, 0, 1, 0, 1));

    // 공통 공격 카드
    bool E_WideStrike[3][3] = { {true, true, true}, {true, true, true}, {true, true, true} };
    AddCard(std::make_shared<C_Attack>("E_WideStrike", 15, 0, 10, E_WideStrike));

    bool E_LineAttack[3][3] = { {false, false, false}, {true, true, true}, {false, false, false} };
    AddCard(std::make_shared<C_Attack>("E_LineAttack", 10, 0, 15, E_LineAttack));

    // 몬스터 타입에 따른 고유 공격 카드 추가 및 가중치 설정
    if (type == EnemyType::Sesshomaru) {
        bool DragonStrike[3][3] = { {false, true, false}, {true, true, true}, {false, true, false} };
        AddCard(std::make_shared<C_Attack>("DragonStrike", 20, 0, 20, DragonStrike));
        AddCardWeight("DragonStrike", 3);
    }
    else if (type == EnemyType::Bankotsu) {
        bool Banryu[3][3] = { {true, false, true}, {false, true, false}, {true, false, true} };
        AddCard(std::make_shared<C_Attack>("BanRyu", 25, 0, 25, Banryu));
        AddCardWeight("BanRyu", 3);
    }

    // 공통 카드 가중치 설정
    AddCardWeight("E_MoveRight", 1);
    AddCardWeight("E_MoveLeft", 1);
    AddCardWeight("E_MoveUp", 1);
    AddCardWeight("E_MoveDown", 1);
    AddCardWeight("E_WideStrike", 2);
    AddCardWeight("E_LineAttack", 2);
}

std::shared_ptr<Card> Enemy::GetRandomCard(int playerX, int playerY, int enemyX, int enemyY)
{
    // 플레이어와 적 사이의 거리를 계산
    int distanceX = std::abs(playerX - enemyX);
    int distanceY = std::abs(playerY - enemyY);

    if (distanceX <= 1 && distanceY <= 1) {
        if (type == EnemyType::Sesshomaru) {
            cardWeights["DragonStrike"] = 5;
        }
        else if (type == EnemyType::Bankotsu) {
            cardWeights["BanRyu"] = 5;
        }
        else {
            cardWeights["E_WideStrike"] = 4;
            cardWeights["E_LineAttack"] = 4;
        }
    }
    else {
        if (type == EnemyType::Sesshomaru) {
            cardWeights["DragonStrike"] = 3;
        }
        else if (type == EnemyType::Bankotsu) {
            cardWeights["BanRyu"] = 3;
        }
        else {
            cardWeights["E_WideStrike"] = 2;
            cardWeights["E_LineAttack"] = 2;
        }
    }

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