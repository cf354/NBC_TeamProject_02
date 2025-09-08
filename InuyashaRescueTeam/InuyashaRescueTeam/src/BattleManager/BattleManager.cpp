#include "BattleManager/BattleManager.h"
#include "Card/C_Move.h"
#include "Card/C_Attack.h"
#include "Card/C_Guard.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "BattleUI/CardUI.h"
#include "ImagePrinter.h"



void BattleManager::Init(std::shared_ptr<Player>p, std::shared_ptr<Enemy>e)
{
    player = p;
    enemy = e;
    
    field.PlayerPositionX = 0;
    field.PlayerPositionY = 1;
    field.EnemyPositionX = 3;
    field.EnemyPositionY = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            field.battlegrid[i][j] = 0;
        }
    }
    field.battlegrid[field.PlayerPositionY][field.PlayerPositionX] = 1;
    field.battlegrid[field.EnemyPositionY][field.EnemyPositionX] = 2;
    _Grid.ReSet_Characters();
}

void BattleManager::StartBattle()
{
    //player.hide

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; // 커서를 보이지 않게 설정
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    std::cout << "전투 시작!\n";

    _HPTEXT.Draw();
    _ENTEXT.Draw();
    _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, INU_BATTLE);
    _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, enemy->GetSpriteFileFath());
    _Grid.Draw();
    _Log.Draw();

    _Player_HPBar.SetMaxValue(player->GetMAXHP());
    _Player_ENBar.SetMaxValue(player->GetMAXStamina());

    _Player_HPBar.SetValue(player->GetHP());
    _Player_ENBar.SetValue(player->GetStamina());

    _Enemy_HPBar.SetMaxValue(enemy->GetMAXHP());
    _Enemy_ENBar.SetMaxValue(enemy->GetMAXStamina());

    _Enemy_HPBar.SetValue(enemy->GetHP());
    _Enemy_ENBar.SetValue(enemy->GetStamina());

    _Player_HPBar.Draw();
    _Player_ENBar.Draw();

    _Enemy_HPBar.Draw();
    _Enemy_ENBar.Draw();

    //_HP

    //ShowUI();

    if (auto a = dynamic_cast<Boss*>(enemy.get())) {
        SOUND_MANAGER->PlayBgm(BGMType::BossTheme);
    }
    else {
        SOUND_MANAGER->PlayBgm(BGMType::BattleField);
    }

    while (!player->IsDead() && !enemy->IsDead()) {
        //field.field_print();

        std::cin.get();
        std::shared_ptr<Card> pCard = PlayerTurn();
        while (auto a = dynamic_cast<C_Move*>(pCard.get())) {           
            if (field.MoveCheck(a->M_GetX() * a->M_GetDistance(), a->M_GetY() * a->M_GetDistance(), 1)) {
                
                break;
            }
            _Log.PrintLog("이동할 수 없습니다");
            pCard = PlayerTurn();
        }
        while (pCard->C_GetCost() > player->GetStamina())
        {
            _Log.PrintLog("스태미나가 부족합니다!");
            pCard = PlayerTurn();
        }


        // 적 턴 시작 시 플레이어와 적의 위치를 GetRandomCard 함수에 전달
        std::shared_ptr<Card> eCard = enemy->GetRandomCard(field.PlayerPositionX, field.PlayerPositionY, field.EnemyPositionX, field.EnemyPositionY);
        
        while (auto a = dynamic_cast<C_Move*>(eCard.get())) {
            if (field.MoveCheck(a->M_GetX() * a->M_GetDistance(), a->M_GetY() * a->M_GetDistance(), 2)) {
                break;
            }           
            eCard = enemy->GetRandomCard(field.PlayerPositionX, field.PlayerPositionY, field.EnemyPositionX, field.EnemyPositionY);
        }
        while (eCard->C_GetCost() > enemy->GetStamina())
        {            
            eCard = enemy->GetRandomCard(field.PlayerPositionX, field.PlayerPositionY, field.EnemyPositionX, field.EnemyPositionY);
        }
        _Log.PrintLog(enemy->GetName() + "이(가) [" + eCard->C_GetName() + "] 카드를 선택했다!");
        //std::cout << enemy->GetName()<<   "이(가) [" << eCard->C_GetName() << "] 카드를 선택했다!\n";
        //
        _Grid.ReSet_Characters();

        _Grid.Draw();
        Resolve(pCard, eCard, field);
        player->RecoverStamina(15);
        enemy->RecoverStamina(10);

        _Player_HPBar.SetValue(player.get()->GetHP());
        _Player_ENBar.SetValue(player.get()->GetStamina());

        _Enemy_HPBar.SetValue(enemy.get()->GetHP());
        _Enemy_ENBar.SetValue(enemy.get()->GetStamina());

        _Player_HPBar.Draw();
        _Player_ENBar.Draw();

        _Enemy_HPBar.Draw();
        //ShowUI(); // 가중치 배율 들어가면 Enemy HP 오른쪽에 ★배치 / 한번 표시되면 이후로 안사라지는 버그 있음.
        _Enemy_ENBar.Draw();

        _Grid.Draw();


    }
    EndBattle();
}


void BattleManager::ShowUI()//하빈
{
    // 플레이어와 적 사이의 거리를 계산
    int distanceX = std::abs(field.PlayerPositionX - field.EnemyPositionX);
    int distanceY = std::abs(field.PlayerPositionY - field.EnemyPositionY);

    // 3x3 범위 안에 있는지 확인
    bool isInAttackRange = (distanceX <= 1 && distanceY <= 1);

    //-------------임시 테스트용---------------
    //std::cout << "==== 전투 UI ====\n";
    //std::cout << player->GetName() << " HP: " << player->GetHP() << " Stamina: " << player->GetStamina()
    //	<< " | " << enemy->GetName() << " HP: " << enemy->GetHP() << " Stamina: " << enemy->GetStamina();

    if (isInAttackRange) {
        std::cout << " ★"; // 공격 가중치 범위 안에 있을 때 ★ 표시
    }
    std::cout << "\n";
}



std::shared_ptr<Card> BattleManager::PlayerTurn()
{
    std::vector<std::shared_ptr<Card>> card = player->GetDeck();
    _CardUI.Draw();
    _CardUI.PrintCards(card);
    return _CardUI.ChoseCard(card);
}

void BattleManager::Resolve(std::shared_ptr<Card> pCard, std::shared_ptr<Card> eCard, BattleField& field)
{
    //std::cout << "행동 실행!\n";
    int pCardDEF = 0;
    int eCardDEF = 0;

    bool isEnemyCharacterSetted = false;

    // 플레이어 행동
    if (auto moveCard = dynamic_cast<C_Move*>(pCard.get())) //플레이어 이동
    {
        field.field_move(moveCard->M_GetX()*moveCard->M_GetDistance(), moveCard->M_GetY()*moveCard->M_GetDistance(), 1);
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, INU_BATTLE);
    }
    if (auto moveCard = dynamic_cast<C_Move*>(eCard.get())) {//적 이동 
       
        field.field_move(moveCard->M_GetX(), moveCard->M_GetY(), 2);
        _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, enemy->GetSpriteFileFath());
        isEnemyCharacterSetted = true;
        _Log.PrintLog("적이 이동했습니다.");

    }
    //체력 OR 스태미나 힐
    if (auto HPheal = dynamic_cast<C_HealHP*>(pCard.get())){
        player->SetHP(player->GetHP() + HPheal->GetHamount());
        _Log.PrintLog("체력을 "+std::to_string(HPheal->GetHamount())+"만큼 회복했다.");
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, INU_BATTLE);
    }

    if (auto Staminaheal = dynamic_cast<C_HealStamina*>(pCard.get())) {
        player->SetStamina(player->GetStamina() + Staminaheal->GetHamount());
        _Log.PrintLog("스태미나를 " + std::to_string(Staminaheal->GetHamount()) + "만큼 회복했다.");
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, INU_BATTLE);
    }

    //적 이동
    if (auto defenseCard = dynamic_cast<C_Guard*>(pCard.get())) //플레이어 방어
    {
        pCardDEF += defenseCard->G_GetDEF();
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, INU_BATTLE);
        _Log.PrintLog("방어가 " + std::to_string(defenseCard->G_GetDEF()) + "만큼 상승했다.");
    }
    if (auto defenseCard = dynamic_cast<C_Guard*>(eCard.get())) {//적 방어
        eCardDEF += defenseCard->G_GetDEF();
        _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, enemy->GetSpriteFileFath());
        isEnemyCharacterSetted = true;
        _Log.PrintLog("적의 방어가 " + std::to_string(eCardDEF) + "만큼 상승했다.");
    }


    if (auto attackCard = dynamic_cast<C_Attack*>(pCard.get())) //플레이어 공격
    {
        std::vector<std::shared_ptr <Card>>* AllCardsList = GAME_MANAGER->GetAllCardsList();

        SOUND_MANAGER->PlaySE(SOUND_MANAGER->GetCardSEType(attackCard->C_GetName()));

        player->SetStamina(player->GetStamina() - attackCard->C_GetCost());
        
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, INU_BATTLE);
        if (!isEnemyCharacterSetted) {
            _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, enemy->GetSpriteFileFath());
            isEnemyCharacterSetted = true;
        }
        _Grid.PaintBlocks(field.PlayerPositionX, field.PlayerPositionY, attackCard->A_GetRange(), Color::RED);

        if (HitCheck(1, attackCard)) {
            int hitdamage = attackCard->A_GetATK() + player->GetATK() - enemy->GetDEF() - eCardDEF;
            if (hitdamage < 0) hitdamage = 0;
            enemy->TakeDamage(hitdamage);
            _Log.PrintLog("플레이어가 적에게 " + std::to_string(hitdamage) + "의 피해를 입혔다.");
        }
        else {
            _Log.PrintLog("공격에 실패했다.");
        }
    }     
    if (auto attackCard = dynamic_cast<C_Attack*>(eCard.get())) {//적 공격
        if (enemy->GetStamina() < attackCard->C_GetCost()) {
            _Log.PrintLog("적의 스태미나가 부족합니다.");
        }
        else {
            if (!isEnemyCharacterSetted) {
                _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, enemy->GetSpriteFileFath());
                isEnemyCharacterSetted = true;
            }
            _Grid.PaintBlocks(field.EnemyPositionX, field.EnemyPositionY, attackCard->A_GetRange(), Color::BLUE);

            enemy->SetStamina(enemy->GetStamina() - attackCard->C_GetCost());

            if (HitCheck(2, attackCard)) {
                int hitdamage = attackCard->A_GetATK() + enemy->GetATK() - player->GetDEF() - pCardDEF;
                if (hitdamage < 0) hitdamage = 0;
                player->TakeDamage(hitdamage);
                _Log.PrintLog("적이 플레이어에게 " + std::to_string(hitdamage) + "의 피해를 입혔다.");
            }
            else {
                _Log.PrintLog("적의 공격이 실패했다.");
            }
        }
    }
}

bool BattleManager::HitCheck(int Entity, C_Attack* card)
{
    int RposX = field.PlayerPositionX - field.EnemyPositionX;
    int RposY = field.PlayerPositionY - field.EnemyPositionY;
    if (RposX > 1 || RposX < -1 || RposY > 1 || RposY < -1) {
        return false;
    }
    if (Entity == 1)
    {
        return card->A_GetRange()[1 - RposY][1 - RposX];
    }
    else if (Entity == 2) {
        return card->A_GetRange()[1 + RposY][1 + RposX];
    }
    else {
        std::cout << "Wrong input HitCheck" << std::endl;
        return false;
    }
}

void BattleManager::EndBattle()
{
    if (player->IsDead()) {
        _Log.PrintLog("플레이어 패배...");
        exit(0);
    }
    else {
        _Log.PrintLog("적 처치 성공!");
        player->AddEXP(enemy->getExp());
        player->SetMoney(player->GetMoney() + enemy->getmoney());
        if (auto a = dynamic_cast<Boss*>(enemy.get())) {
            SOUND_MANAGER->PlayBgm(BGMType::EndBgm);
            ImagePrinter* imagePrinter = new ImagePrinter();
            imagePrinter->PlayGIF(KAGOME_GIF, 10, 300, 0, 0);
            exit(0);
        }
        enemy.reset();
        
    }
    system("cls");
    GAME_MANAGER->SetState(GameManagerState::Map);
}

