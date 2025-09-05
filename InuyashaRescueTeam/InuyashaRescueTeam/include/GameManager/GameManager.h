#pragma once
#include <iostream>
#include "Entities.h"
#include "Cards.h"
#include "BattleManager/BattleManager.h"
#include "Common/Singleton.h"

class GameManager : public Singleton<GameManager>
{
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;

public:
    GameManager();
    void Run();

    std::weak_ptr<Player> GetPlayer();
};

#define GAME_MANAGER (GameManager::GetInstance())
