#pragma once
#include <iostream>
#include "Entities.h"
#include "Cards.h"
#include "BattleManager/BattleManager.h"


class GameManager {
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;

public:
    GameManager() {
        player = std::make_shared<Player>("이누야샤", 1, 100, 100, 10, 5);
        enemy = std::make_shared<Enemy>("셋쇼마루", 1, 50, 30, 8, 3, 10, 20);

        // 기본 카드 몇 장 추가
        player->AddCard(std::make_shared<C_Move>("MoveRight", 0, 0, 1, 1, 0));// C_Move(std::string n,int C, int G, int d, int dirx, int diry) :distance(d), x(dirx), y(diry) { Name = n; Cost = C; Gold = G; };
        player->AddCard(std::make_shared<C_Move>("MoveLeft", 0, 0, 1, -1, 0));
        player->AddCard(std::make_shared<C_Move>("MoveUp", 0, 0, 1, 0, -1));
        player->AddCard(std::make_shared<C_Move>("MoveDown", 0, 0, 1, 0, 1));


        bool BladeStrike[3][3] = { {false,true,false},{false,true,false},{false,true,false} };
        player->AddCard(std::make_shared<C_Attack>("BladeStrike", 25, 0, 30, BladeStrike));// C_Attack(std::string n, int C, int G, int A, bool r[3][3]) :ATK(A), Range(r) { Name = n; Cost = C; Gold = G; }
        bool BladesOfBlood[3][3] = { {false,true,false},{true,true,true},{false,true,false} };
        player->AddCard(std::make_shared<C_Attack>("BladesOfBlood", 25, 0, 25, BladesOfBlood));
        bool IronReaver[3][3] = { {true,false,true},{false,true,false},{true,false,true} };
        player->AddCard(std::make_shared<C_Attack>("IronReaver", 35, 0, 25, IronReaver));
        bool WindScar[3][3] = { {false,false,false},{false,true,false},{true,true,true} };
        player->AddCard(std::make_shared<C_Attack>("WindScar", 50, 0, 50, WindScar));
        player->AddCard(std::make_shared<C_Guard>("Guard", 0, 0, 15));
        //C_Guard(std::string n, int C, int G, int D) :DEF(D) {Name = n; Cost = C; Gold = G;}
        
        enemy->AddCard(std::make_shared<C_Move>("MoveDown", 0, 0, 1, 0, -1));

    }

    void Run() {
        BattleManager battle(player, enemy);
        battle.StartBattle();
    }
};
