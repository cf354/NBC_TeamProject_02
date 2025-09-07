#include "GameManager\GameManager.h"
#include "Map/MapManager.h"
#include "Common/ConsolePrinter.h"
#include "SoundManager/SoundManager.h"
#include "Common/RandomManager.h"


void GameManager::Init()
{
    RANDOM_MANAGER->Init();
    CONSOLE_PRINTER->Init();

#pragma region ExampleBattleInit
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
    
    //사운드
    SOUND_MANAGER->Init();
    BATTLE_MANAGER->Init(player, enemy);
    

    enemy->AddCard(std::make_shared<C_Move>("MoveDown", 0, 0, 1, 0, -1));
#pragma endregion

    MAP_MANAGER->EnterNextStage();
}

void GameManager::Update()
{
    CONSOLE_PRINTER->Update();
    MAP_MANAGER->UpdatePlayer();
    MAP_MANAGER->Draw();
    CONSOLE_PRINTER->Render();
}

void GameManager::Run()
{
    BATTLE_MANAGER->StartBattle();
}

std::weak_ptr<Player> GameManager::GetPlayer()
{
    return player;
}

std::vector<std::shared_ptr <Card>>* GameManager::GetAllCardsList()
{
    return &AllCardsList;
}