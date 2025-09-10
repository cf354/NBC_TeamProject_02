#include "GameManager/GameManager.h"
#include "Map/Managers/MapManager.h"
#include "Map/Managers/SceneManager.h"
#include "Common/TimeManager.h"
#include "Common/ConsolePrinter.h"
#include "SoundManager/SoundManager.h"
#include "Common/RandomManager.h"
#include "Merchant/Merchant.h"
#include <conio.h>
#include "InputManager/InputManager.h"
#include "ImagePrinter.h"
#include "Entity/Enemy.h"
#include "Entity/Boss.h"
#include "Map/Managers/UIManager.h"

void GameManager::Init()
{
    RANDOM_MANAGER->Init();
    TIME->Init();
    CONSOLE_PRINTER->Init();
    SCENE_MANAGER->Init();
    UI_MANAGER->Init();

    //사운드
    SOUND_MANAGER->Init();
#pragma region ExampleBattleInit
    player = std::make_shared<Player>("이누야샤", 1, 100, 100, 10, 5, INU_BATTLE);

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


    AllCardsList.emplace_back(std::make_shared<C_Guard>("Guard", 0, 10, 15)); //8  //C_Guard(std::string n, int C, int G, int D) :DEF(D) {Name = n; Cost = C; Gold = G;}

    

    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveRight", 0, 5, 2, 1, 0)); // 9
    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveLeft", 0, 10, 2, -1, 0)); // 10
    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveUp", 0, 15, 2, 0, -1)); // 11
    AllCardsList.emplace_back(std::make_shared<C_Move>("DoubleMoveDown", 0, 20, 2, 0, 1)); // 12

    bool Adamant_Barrage[3][3] = {
        {1,1,1},
        {1,1,1},
        {1,1,1} };
    AllCardsList.emplace_back(std::make_shared<C_Attack>("Adamant_Barrage", 70, 100, 30, Adamant_Barrage));//13

    bool Backlash_Wave[3][3]{
        {0,0,1},
        {0,1,1},
        {0,0,1}
    };
    AllCardsList.emplace_back(std::make_shared<C_Attack>("Backlash_Wave", 50, 70, 40, Backlash_Wave));//14

    AllCardsList.emplace_back(std::make_shared<C_HealHP>("Heal", 20, 0, 30)); //15  C_HealHP(std::string n, int C, int G,int h) :Card(n, C, G),Hamount(h)
    AllCardsList.emplace_back(std::make_shared<C_HealStamina>("Energy UP", 0, 0, 10)); //16  C_HealStamina(std::string n, int C, int G, int h) :Card(n, C, G), Samount(h)
    AllCardsList.emplace_back(std::make_shared<MasterCard>(" ", 0, 0));

    // 기본 카드 몇 장 추가
    player->AddCard(AllCardsList[0]); // MoveRight
    player->AddCard(AllCardsList[1]); // MoveLeft
    player->AddCard(AllCardsList[2]); // MoveUp
    player->AddCard(AllCardsList[3]); // MoveDown


    player->AddCard(AllCardsList[4]); // BladeStrike
    player->AddCard(AllCardsList[5]); // BladesOfBlood
    player->AddCard(AllCardsList[6]); // IronReaver
    player->AddCard(AllCardsList[7]); // WindScar
    player->AddCard(AllCardsList[8]);
    player->AddCard(AllCardsList[17]);

#pragma endregion

    SetState(GameManagerState::Title);
}

void GameManager::Update()
{
    TIME->Update();
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

void GameManager::Battle(bool isBoss)
{
    shared_ptr<Enemy> enemy;

    if (isBoss)
    {
        // 나락 (Boss)
        enemy = std::make_shared<Boss>("나락", 2, 200, 150, 16, 6, 40, 40, NARAK, EnemyType::Naraku);
    }
    else
    {
        // normal 적이 더 많이 나올텐데 걍 함
        int enemyType = RANDOM_MANAGER->Range(0, (int)EnemyType::MAX);
        switch ((EnemyType)enemyType)
        {
            case EnemyType::Sesshomaru:
                // 셋쇼마루
                enemy = std::make_shared<Enemy>("셋쇼마루", 1, 100, 80, 8, 3, 80, 25, SESSHO, EnemyType::Sesshomaru);
                break;
            case EnemyType::Bankotsu:
                // 반코츠
                enemy = std::make_shared<Enemy>("반코츠", 1, 80, 60, 10, 5, 60, 30, BANKOTSU, EnemyType::Bankotsu);
                break;
            default:
                // 기본 적으로 설정
                enemy = std::make_shared<Enemy>("역발의 유라", 1, 60, 40, 5, 2, 40, 15, YURA, EnemyType::Normal);
                break;
        }
    }

    // 이 부분에서 InitDeck()을 호출합니다.
    enemy->InitDeck();

    BATTLE_MANAGER->Init(player, enemy);
    SetState(GameManagerState::Battle);
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
    case GameManagerState::Ending:
        EnterEnding();
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
    case GameManagerState::Ending:
        UpdateEnding();
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
    case GameManagerState::Ending:
        ExitEnding();
        break;
    }
}

void GameManager::EnterTitle()
{
    ImagePrinter* imagePrinter = new ImagePrinter();
    imagePrinter->DrawImage(KEY, 0, 0);
    SOUND_MANAGER->PlayBgm(BGMType::StartScene);
}

void GameManager::UpdateTitle()
{
    if (_kbhit())
    {
        SetState(GameManagerState::Map);
    }
}

void GameManager::ExitTitle()
{
    system("cls");
}

void GameManager::EnterMap()
{
    MAP_MANAGER->PlayStageBGM();
}

void GameManager::UpdateMap()
{
    CONSOLE_PRINTER->Update();
    SCENE_MANAGER->Update();
    UI_MANAGER->Update();

    SCENE_MANAGER->Render();
    UI_MANAGER->Render();
    CONSOLE_PRINTER->Render();
}

void GameManager::ExitMap()
{
    UI_MANAGER->ShowInventory(false);
    UpdateMap();
    SOUND_MANAGER->PlaySE(SEType::MapChangeSE);
    CONSOLE_PRINTER->ScreenTransition_Swipe();
    CONSOLE_PRINTER->SetActiveBuffer(0);
    CONSOLE_PRINTER->ScreenClear();
}

void GameManager::EnterBattle()
{
    SOUND_MANAGER->PlayBgm(BGMType::BattleField);
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

void GameManager::EnterEnding()
{
    ImagePrinter* imagePrinter = new ImagePrinter();
    imagePrinter->PlayGIF(KAGOME_GIF, 10, 300, 0, 0);
}

void GameManager::UpdateEnding()
{
}

void GameManager::ExitEnding()
{
}