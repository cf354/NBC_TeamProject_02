#pragma once
#include <iostream>
#include "Entities.h"
#include "Cards.h"
#include "BattleManager/BattleManager.h"
#include "Common/Singleton.h"
#include "GameManager/GameManager.h"
#include "SoundManager/SoundManager.h"

enum class GameManagerState
{
    None = -1,
    Title,
    Map,
    Battle,
    Merchant,
    Ending,
};

class GameManager : public Singleton<GameManager>
{
private:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr <Card>> AllCardsList;

    GameManagerState currState = GameManagerState::None;
    

public:
    void Init();
    void Update();

    std::weak_ptr<Player> GetPlayer();
    std::vector<std::shared_ptr <Card>>* GetAllCardsList();

    void Battle(int enemyId);

    void SetState(GameManagerState state);

private:
    void EnterState(GameManagerState state);
    void UpdateState(GameManagerState state);
    void ExitState(GameManagerState state);

    void EnterTitle();
    void UpdateTitle();
    void ExitTitle();

    void EnterMap();
    void UpdateMap();
    void ExitMap();

    void EnterBattle();
    void UpdateBattle();
    void ExitBattle();

    void EnterMerchant();
    void UpdateMerchant();
    void ExitMerchant();

    void EnterEnding();
    void UpdateEnding();
    void ExitEnding();
};

#define GAME_MANAGER (GameManager::GetInstance())