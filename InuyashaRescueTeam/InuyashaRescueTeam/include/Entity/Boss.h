#pragma once
#include "Entity/Enemy.h"
#include <iostream>
#include <vector>
#include <map>
#include "Card/Card.h"

// Boss Ŭ����: Enemy�� ��ӹ޾� ���� ���� ī�� ���� ������ ����
class Boss : public Enemy {
private:
    int phase = 1;   // ���� ���� ������ (ü�� ���� � ���� ����)

public:
    Boss(std::string n, int lv, int h, int s, int a, int d, int dm, int de)
        : Enemy(n, lv, h, s, a, d, dm, de) {}

    // ���� ���� ī�� �� �ʱ�ȭ
    void InitDeck();

    // ����ġ ��� ī�� ���� (������ ��ȯ ���� ����)
    std::shared_ptr<Card> GetRandomCard(int playerX, int playerY, int enemyX, int enemyY) override;

    ~Boss() {}
};
