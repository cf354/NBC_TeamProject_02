#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Entities.h"
#include "Cards.h"
#include "BattleManager/BattleManager.h"

// GameManager 클래스의 모든 구현을 헤더에 포함합니다.
class GameManager {
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;

public:
    GameManager() {
        player = std::make_shared<Player>("이누야샤", 1, 100, 100, 10, 5);
        enemy = std::make_shared<Enemy>("셋쇼마루", 1, 50, 50, 8, 3, 10, 20);

        // 기본 카드 몇 장 추가
        player->AddCard(std::make_shared<C_Move>("MoveRight", 0, 0, 1, 1, 0));
        player->AddCard(std::make_shared<C_Move>("MoveLeft", 0, 0, 1, -1, 0));
        player->AddCard(std::make_shared<C_Move>("MoveUp", 0, 0, 1, 0, -1));
        player->AddCard(std::make_shared<C_Move>("MoveDown", 0, 0, 1, 0, 1));

        bool BladeStrike[3][3] = { {false,true,false},{false,true,false},{false,true,false} };
        player->AddCard(std::make_shared<C_Attack>("BladeStrike", 25, 0, 30, BladeStrike));
        bool BladesOfBlood[3][3] = { {false,true,false},{true,true,true},{false,true,false} };
        player->AddCard(std::make_shared<C_Attack>("BladesOfBlood", 25, 0, 25, BladesOfBlood));
        bool IronReaver[3][3] = { {true,false,true},{false,true,false},{true,false,true} };
        player->AddCard(std::make_shared<C_Attack>("IronReaver", 35, 0, 25, IronReaver));
        bool WindScar[3][3] = { {false,false,false},{false,true,false},{true,true,true} };
        player->AddCard(std::make_shared<C_Attack>("WindScar", 50, 0, 50, WindScar));
        player->AddCard(std::make_shared<C_Guard>("Guard", 0, 0, 15));

        // **적(Enemy) 카드 덱 구성 및 가중치 부여**
        enemy->AddCard(std::make_shared<C_Move>("E_MoveRight", 0, 0, 1, 1, 0));
        enemy->AddCard(std::make_shared<C_Move>("E_MoveLeft", 0, 0, 1, -1, 0));
        enemy->AddCard(std::make_shared<C_Move>("E_MoveUp", 0, 0, 1, 0, -1));
        enemy->AddCard(std::make_shared<C_Move>("E_MoveDown", 0, 0, 1, 0, 1));

        bool E_WideStrike[3][3] = { {true, true, true}, {true, true, true}, {true, true, true} };
        enemy->AddCard(std::make_shared<C_Attack>("E_WideStrike", 15, 0, 10, E_WideStrike));

        bool E_LineAttack[3][3] = { {false, false, false}, {true, true, true}, {false, false, false} };
        enemy->AddCard(std::make_shared<C_Attack>("E_LineAttack", 10, 0, 15, E_LineAttack));

        // 이동 카드의 가중치를 1, 공격 카드의 가중치를 2로 설정 (공격을 더 선호)
        enemy->AddCardWeight("E_MoveRight", 1);
        enemy->AddCardWeight("E_MoveLeft", 1);
        enemy->AddCardWeight("E_MoveUp", 1);
        enemy->AddCardWeight("E_MoveDown", 1);
        enemy->AddCardWeight("E_WideStrike", 2);
        enemy->AddCardWeight("E_LineAttack", 2);
    }

    void Run() {
        BattleManager battle(player, enemy);
        battle.StartBattle();
    }
};