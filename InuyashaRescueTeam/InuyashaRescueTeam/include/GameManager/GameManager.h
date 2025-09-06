#pragma once
#include <iostream>
#include "Entities.h"
#include "Cards.h"
#include "BattleManager/BattleManager.h"
#include "Common/Singleton.h"
#include "GameManager/GameManager.h"
#include "SoundManager/SoundManager.h"

class GameManager : public Singleton<GameManager>
{
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    std::vector<std::shared_ptr <Card>> AllCardsList;
    SoundManager sound;

public:
    void Init();
    void Update();
    void Run();
    SoundManager &GetSoundManager();

    std::weak_ptr<Player> GetPlayer();
    std::vector<std::shared_ptr <Card>>* GetAllCardsList();
};

#define GAME_MANAGER (GameManager::GetInstance())