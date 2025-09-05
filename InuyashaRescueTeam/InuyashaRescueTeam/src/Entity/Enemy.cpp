#include "Entity/Enemy.h"
#include "Card/C_Attack.h"
#include <random>

std::shared_ptr<Card> Enemy::GetRandomCard(int playerX, int playerY, int enemyX, int enemyY)
{
    // 플레이어와 적 사이의 거리를 계산
    int distanceX = std::abs(playerX - enemyX);
    int distanceY = std::abs(playerY - enemyY);

    // 3x3 범위 안에 플레이어가 있는지 확인
    if (distanceX <= 1 && distanceY <= 1) {
        // 3x3 범위 안에 있다면 공격 가중치를 4로 설정
        cardWeights["E_WideStrike"] = 4;
        cardWeights["E_LineAttack"] = 4;
    }
    else {
        // 그렇지 않다면 기본 가중치인 2로 설정
        cardWeights["E_WideStrike"] = 2;
        cardWeights["E_LineAttack"] = 2;
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