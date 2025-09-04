#pragma once
#include "Entity.h"
#include <vector>
#include <iostream>
#include "Card\Card.h"

class Player : public Entity {
private:
    int money;
    int exp;
    std::vector<std::shared_ptr<Card>> deck;
    int TurnHealStamina = 15;

public:
    Player(std::string n, int lv, int h, int s, int a, int d)
        : Entity(n, lv, h, s, a, d), money(0), exp(0) {
    }

    int getTurnHealStamina() { return TurnHealStamina; }
    int getMoney() { return money; }
    int getExp() { return exp; }

    void setTurnHealStamina(int n) { TurnHealStamina = n; }
    void setMoney(int n) { money = n; }
    void setExp(int n);
    void LevelUp();
    

    void AddCard(const std::shared_ptr<Card> c) { deck.push_back(c); }
    std::vector<std::shared_ptr<Card>> GetCards() { return deck; }

};

