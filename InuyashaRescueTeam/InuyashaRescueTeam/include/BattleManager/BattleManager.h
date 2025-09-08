#pragma once
#include <iostream>
#include "Cards.h"
#include "Entities.h"
#include "battlefield\battlefield.h"
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include "BattleUI/BattleUIGroup.h"
#include "Common\Singleton.h"
#include "GameManager/GameManager.h"

class BattleManager:public Singleton<BattleManager> {
private: 
    std::shared_ptr<Player> player;

    std::shared_ptr<Enemy> enemy;
    sf::Music bgm;

    //BattleUI
    Progressbar _Player_HPBar;
    Text _HPTEXT;
    Progressbar _Enemy_HPBar;
    Progressbar _Player_ENBar;
    Text _ENTEXT;
    Progressbar _Enemy_ENBar;
    BattleGrid _Grid;
    CardUI _CardUI;
    BattleLog _Log;

public:
    BattleManager()
        : _Player_HPBar(97, 0, 0, 0, Color::YELLOW, Color::RED, true)
        , _HPTEXT(_Player_HPBar.GetRight() + 1, _Player_HPBar.GetBottom() - 1, 4, "▥HP▥", YELLOW, BLACK)
        , _Enemy_HPBar(97, _HPTEXT.GetRight(), _HPTEXT.GetBottom() - 1, 0, Color::YELLOW, Color::RED, false)
        , _Player_ENBar(97, _Player_HPBar.GetLeft(), _Player_HPBar.GetBottom(), 0, Color::YELLOW, Color::BROWN, true)
        , _ENTEXT(_Player_ENBar.GetRight() + 1, _Player_ENBar.GetBottom() - 1, 4, "▥ST▥", YELLOW, BLACK)
        , _Enemy_ENBar(97, _ENTEXT.GetRight(), _ENTEXT.GetBottom() - 1, 0, Color::YELLOW, Color::BROWN, false)
        , _Grid(200, 42, _Player_ENBar.GetLeft(), _Player_ENBar.GetBottom())
        , _CardUI(200, 16, _Player_ENBar.GetLeft(), _Player_ENBar.GetBottom() + 5)
        , _Log(200, 6, _Grid.GetLeft(), _Grid.GetBottom())
    {
        
    }

    BattleField field;
public:
    void Init(std::shared_ptr<Player>p,std::shared_ptr<Enemy>e);
    
    void StartBattle();
    
private:
    
    void ShowUI();
    std::shared_ptr<Card> PlayerTurn();
    void Resolve(std::shared_ptr<Card> pCard, std::shared_ptr<Card> eCard, BattleField& field);
    bool HitCheck(int Entity, C_Attack* card);//Entity 1: player 2: enemy 3:player&enemy(미구현)
    void EndBattle();
};

#define BATTLE_MANAGER (BattleManager::GetInstance())
