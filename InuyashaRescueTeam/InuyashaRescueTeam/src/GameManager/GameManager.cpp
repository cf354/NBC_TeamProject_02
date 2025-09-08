#include "GameManager\GameManager.h"
#include "Map/MapManager.h"
#include "Common/ConsolePrinter.h"
#include "SoundManager/SoundManager.h"
#include "Common/RandomManager.h"
#include "Merchant\Merchant.h"
#include <conio.h>

void GameManager::Init()
{
    RANDOM_MANAGER->Init();
    CONSOLE_PRINTER->Init();

#pragma region EnemySelection

    std::cout << "적이 나타났다! (임시 적 선택 UI)\n";
    std::cout << "1. 셋쇼마루 (Enemy)\n";
    std::cout << "2. 나락 (Boss)\n";
    std::cout << "선택: ";

    char choice;
    while (true) {
        choice = _getch();
        if (choice == '1') {
            enemy = std::make_shared<Enemy>("셋쇼마루", 1, 50, 30, 8, 3, 10, 20);
            std::cout << "\n셋쇼마루를 선택했습니다.\n";
            break;
        }
        else if (choice == '2') {
            enemy = std::make_shared<Boss>("나락", 2, 100, 60, 16, 6, 20, 40);
            std::cout << "\n나락을 선택했습니다.\n";
            break;
        }
        else {
            // 잘못된 입력 시, 다시 입력을 받습니다.
            std::cout << "\n잘못된 입력입니다. 1 또는 2를 눌러주세요: \n";
        }
    }
    system("cls");

#pragma endregion EnemySelection

#pragma region ExampleBattleInit
    player = std::make_shared<Player>("이누야샤", 1, 100, 100, 10, 5);
    //enemy = std::make_shared<Enemy>("셋쇼마루", 1, 50, 30, 8, 3, 10, 20); // EnemySelection 으로 적을 고를수 있기 때문에 임시로 추가되어있는 필요없는 부분

    AllCardsList.emplace_back(std::make_shared<C_Move>("MoveRight", 0, 10, 1, 1, 0)); // 0 // C_Move(std::string n,int C, int G, int d, int dirx, int diry) :distance(d), x(dirx), y(diry) { Name = n; Cost = C; Gold = G; };
    AllCardsList.emplace_back(std::make_shared<C_Move>("MoveLeft", 0, 10, 1, -1, 0)); // 1
    AllCardsList.emplace_back(std::make_shared<C_Move>("MoveUp", 0, 10, 1, 0, -1)); // 2
    AllCardsList.emplace_back(std::make_shared<C_Move>("MoveDown", 0, 10, 1, 0, 1)); // 3
    bool BladeStrike[3][3] = {
        {0,1,0},
        {0,1,0},
        {0,1,0} };
    AllCardsList.emplace_back(std::make_shared<C_Attack>("BladeStrike", 25, 15, 30, BladeStrike)); // 4 // C_Attack(std::string n, int C, int G, int A, bool r[3][3]) :ATK(A), Range(r) { Name = n; Cost = C; Gold = G; }
    bool BladesOfBlood[3][3] = {
        {0,1,0},
        {1,1,1},
        {0,1,0} };
    AllCardsList.emplace_back(std::make_shared<C_Attack>("BladesOfBlood", 25, 20, 25, BladesOfBlood)); //5
    bool IronReaver[3][3] = {
        {1,0,1},
        {0,1,0},
        {1,0,1} };
    AllCardsList.emplace_back(std::make_shared<C_Attack>("IronReaver", 35, 25, 25, IronReaver)); // 6
    bool WindScar[3][3] = {
        {0,0,0},
        {0,1,0},
        {1,1,1} };
    AllCardsList.emplace_back(std::make_shared<C_Attack>("WindScar", 50, 30, 50, WindScar)); // 7
    AllCardsList.emplace_back(std::make_shared<C_Guard>("Guard", 0, 10, 15)); // 8 //C_Guard(std::string n, int C, int G, int D) :DEF(D) {Name = n; Cost = C; Gold = G;}

    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveRight", 0, 5, 2, 1, 0)); // 9
    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveLeft", 0, 10, 2, -1, 0)); // 10
    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveUp", 0, 15, 2, 0, -1)); // 11
    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveDown", 0, 20, 2, 0, 1)); // 12

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
    SetState(GameManagerState::Map);
}

void GameManager::Update()
{
    UpdateState(currState);
}

std::weak_ptr<Player> GameManager::GetPlayer()
{
    return player;
}

std::vector<std::shared_ptr <Card>>* GameManager::GetAllCardsList()
{
    return &AllCardsList;
}

void GameManager::SetState(GameManagerState state)
{
    if (currState == state)
        return;

    if (currState != GameManagerState::None)
        ExitState(currState);
    currState = state;
    EnterState(currState);
}

void GameManager::EnterState(GameManagerState state)
{
    switch (state)
    {
        case GameManagerState::Title:
            EnterTitle();
            break;
        case GameManagerState::Map:
            EnterMap();
            break;
        case GameManagerState::Battle:
            EnterBattle();
            break;
        case GameManagerState::Merchant:
            EnterMerchant();
            break;
    }
}

void GameManager::UpdateState(GameManagerState state)
{
    switch (state)
    {
        case GameManagerState::Title:
            UpdateTitle();
            break;
        case GameManagerState::Map:
            UpdateMap();
            break;
        case GameManagerState::Battle:
            UpdateBattle();
            break;
        case GameManagerState::Merchant:
            UpdateMerchant();
            break;
    }
}

void GameManager::ExitState(GameManagerState state)
{
    switch (state)
    {
        case GameManagerState::Title:
            ExitTitle();
            break;
        case GameManagerState::Map:
            ExitMap();
            break;
        case GameManagerState::Battle:
            ExitBattle();
            break;
        case GameManagerState::Merchant:
            ExitMerchant();
            break;
    }
}

void GameManager::EnterTitle()
{
}

void GameManager::UpdateTitle()
{
}

void GameManager::ExitTitle()
{
}

void GameManager::EnterMap()
{
}

void GameManager::UpdateMap()
{
    CONSOLE_PRINTER->Update();
    MAP_MANAGER->UpdatePlayer();
    MAP_MANAGER->Draw();
    CONSOLE_PRINTER->Render();
}

void GameManager::ExitMap()
{
}

void GameManager::EnterBattle()
{
    BATTLE_MANAGER->StartBattle();
}

void GameManager::UpdateBattle()
{
}

void GameManager::ExitBattle()
{
}

void GameManager::EnterMerchant()
{
    Merchant* test = new Merchant();
    test->OpenShop();
}

void GameManager::UpdateMerchant()
{
}

void GameManager::ExitMerchant()
{
}