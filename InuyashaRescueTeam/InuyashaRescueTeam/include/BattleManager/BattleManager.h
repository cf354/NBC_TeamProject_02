#pragma once
#include <iostream>
#include "Cards.h"
#include "Entities.h"
#include "battlefield\battlefield.h"

class BattleManager {
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;


public:
    BattleManager(std::shared_ptr<Player> p, std::shared_ptr<Enemy> e)
        : player(p), enemy(e) {}
    BattleField field;
    void StartBattle();

private:
    void Healstamina();

    void ShowCard(std::vector<std::shared_ptr<Card>> card);
    void ShowUI();
    std::shared_ptr<Card> PlayerTurn();
    void Resolve(std::shared_ptr<Card> pCard, std::shared_ptr<Card> eCard, BattleField& field);
    bool HitCheck(int Entity, C_Attack* card);//Entity 1: player 2: enemy 3:player&enemy(미구현)
    void EndBattle();
};
