#pragma once
#include <iostream>
#include "Cards.h"
#include "Entities.h"
#include "battlefield\battlefield.h"
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include "Common\Singleton.h"
#include "SoundManager/SoundManager.h"
#include "GameManager/GameManager.h"

class BattleManager:public Singleton<BattleManager> {
private: 
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy; 
    BattleField field;
public:
    void Init(std::shared_ptr<Player>p,std::shared_ptr<Enemy>e);
    
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

#define BATTLE_MANAGER (BattleManager::GetInstance())
