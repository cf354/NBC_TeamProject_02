#pragma once
#include <iostream>
#include "Entities.h"
#include "Cards.h"
#include "BattleManager/BattleManager.h"


class GameManager {
public:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    std::vector<std::shared_ptr <Card>> AllCardsList;

public:
    GameManager() {
        player = std::make_shared<Player>("이누야샤", 1, 100, 100, 10, 5);
        enemy = std::make_shared<Enemy>("셋쇼마루", 1, 50, 30, 8, 3, 10, 20);

        AllCardsList.emplace_back(std::make_shared<C_Move>("MoveRight", 0, 0, 1, 1, 0)); // 0 // C_Move(std::string n,int C, int G, int d, int dirx, int diry) :distance(d), x(dirx), y(diry) { Name = n; Cost = C; Gold = G; };
        AllCardsList.emplace_back(std::make_shared<C_Move>("MoveLeft", 0, 0, 1, -1, 0)); // 1
        AllCardsList.emplace_back(std::make_shared<C_Move>("MoveUp", 0, 0, 1, 0, -1)); // 2
        AllCardsList.emplace_back(std::make_shared<C_Move>("MoveDown", 0, 0, 1, 0, 1)); // 3
        bool BladeStrike[3][3] = { {false,true,false},{false,true,false},{false,true,false} };
        AllCardsList.emplace_back(std::make_shared<C_Attack>("BladeStrike", 25, 0, 30, BladeStrike)); // 4 // C_Attack(std::string n, int C, int G, int A, bool r[3][3]) :ATK(A), Range(r) { Name = n; Cost = C; Gold = G; }
        bool BladesOfBlood[3][3] = { {false,true,false},{true,true,true},{false,true,false} };
        AllCardsList.emplace_back(std::make_shared<C_Attack>("BladesOfBlood", 25, 0, 25, BladesOfBlood)); //5
        bool IronReaver[3][3] = { {true,false,true},{false,true,false},{true,false,true} };
        AllCardsList.emplace_back(std::make_shared<C_Attack>("IronReaver", 35, 0, 25, IronReaver)); // 6
        bool WindScar[3][3] = { {false,false,false},{false,true,false},{true,true,true} };
        AllCardsList.emplace_back(std::make_shared<C_Attack>("WindScar", 50, 0, 50, WindScar)); // 7
        AllCardsList.emplace_back(std::make_shared<C_Guard>("Guard", 0, 0, 15)); // 8 //C_Guard(std::string n, int C, int G, int D) :DEF(D) {Name = n; Cost = C; Gold = G;}
        
        AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveRight", 0, 0, 1, 2, 0)); // 9
        AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveLeft", 0, 0, 1, -2, 0)); // 10
        AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveUp", 0, 0, 1, 0, -1)); // 11
        AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveDown", 0, 0, 1, 0, 1)); // 12

        // 기본 카드 몇 장 추가
        player->AddCard(AllCardsList[0]); // MoveRight
        player->AddCard(AllCardsList[1]); // MoveLeft
        player->AddCard(AllCardsList[2]); // MoveUp
        player->AddCard(AllCardsList[3]); // MoveDown

        player->AddCard(AllCardsList[4]); // BladeStrike
        player->AddCard(AllCardsList[5]); // BladesOfBlood
        player->AddCard(AllCardsList[6]); // IronReaver
        player->AddCard(AllCardsList[7]); // WindScar
        player->AddCard(AllCardsList[8]); // Guard
        
        enemy->AddCard(AllCardsList[3]); // MoveDown
    }

    void Run() {
        BattleManager battle(player, enemy);
        battle.StartBattle();
    }

    std::vector<std::shared_ptr <Card>>* GetAllCardsList()
    {
        return &AllCardsList;
    }
};