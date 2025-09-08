#pragma once
#include "Entity/Entity.h"
#include <iostream>
#include <vector>
#include <map>
#include "Card/Card.h"


// 몬스터 종류를 구분하기 위한 열거형
enum class EnemyType {
    Normal,
    Sesshomaru,
    Bankotsu,
    Naraku
};

class Enemy : public Entity {
protected:
    int drop_money;
    int drop_exp;
    std::vector<std::shared_ptr<Card>> deck;
    std::map<std::string, int> cardWeights;
    EnemyType type = EnemyType::Normal;

public:
    // 생성자에 EnemyType 인수를 추가
    Enemy(std::string n, int lv, int h, int s, int a, int d, int dm, int de, EnemyType t)
        : Entity(n, lv, h, s, a, d), drop_money(dm), drop_exp(de), type(t) {}

    // 기본 생성자 (필요할 경우를 위해 추가)
    Enemy(std::string n, int lv, int h, int s, int a, int d, int dm, int de)
        : Enemy(n, lv, h, s, a, d, dm, de, EnemyType::Normal) {}


    int getExp() { return drop_exp; }
    int getmoney() { return drop_money; }
    std::string GetName();
    void AddCard(const std::shared_ptr<Card>& c) { deck.push_back(c); }
    void AddCardWeight(const std::string& cardName, int weight) { cardWeights[cardName] = weight; }

    virtual void InitDeck(); // 덱 초기화 함수 선언
    virtual std::shared_ptr<Card> GetRandomCard(int playerX, int playerY, int enemyX, int enemyY);

    ~Enemy() {};
};