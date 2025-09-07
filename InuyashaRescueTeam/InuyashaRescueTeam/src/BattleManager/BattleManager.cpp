#include "BattleManager/BattleManager.h"
#include "Card/C_Move.h"
#include "Card/C_Attack.h"
#include "Card/C_Guard.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "BattleUI/CardUI.h"



void BattleManager::Init(std::shared_ptr<Player>p, std::shared_ptr<Enemy>e)
{
	player = p;
	enemy = e;
}

void BattleManager::StartBattle()
{
	std::cout << "전투 시작!\n";

    _HPTEXT.Draw();
    _ENTEXT.Draw();
    _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, "@", Color::RED, Color::BLACK);
    _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
    _Grid.Draw();
    _Log.Draw();

    _Player_HPBar.SetValue(player.get()->GetHP());
    _Player_ENBar.SetValue(player.get()->GetStamina());

    _Enemy_HPBar.SetValue(enemy.get()->GetHP());
    _Enemy_ENBar.SetValue(enemy.get()->GetStamina());

    _Player_HPBar.Draw();
    _Player_ENBar.Draw();

    _Enemy_HPBar.Draw();
    _Enemy_ENBar.Draw();


	SOUND_MANAGER->PlayBgm(BGMType::BattleField);
	
	while (!player->IsDead() && !enemy->IsDead()) {
		//field.field_print();

        std::cin.get();

		std::shared_ptr<Card> pCard = PlayerTurn();

		// 적 턴 시작 시 플레이어와 적의 위치를 GetRandomCard 함수에 전달
		std::shared_ptr<Card> eCard = enemy->GetRandomCard(field.PlayerPositionX, field.PlayerPositionY, field.EnemyPositionX, field.EnemyPositionY);
        _Log.PrintLog(enemy->GetName() + "이(가) [" + eCard->C_GetName() +"] 카드를 선택했다!" );
		//std::cout << enemy->GetName()<<   "이(가) [" << eCard->C_GetName() << "] 카드를 선택했다!\n";
        //
        _Grid.Reset_Character_Position();

        _Grid.Draw();

		Resolve(pCard, eCard, field);

        _Player_HPBar.SetValue(player.get()->GetHP());
        _Player_ENBar.SetValue(player.get()->GetStamina());

        _Enemy_HPBar.SetValue(enemy.get()->GetHP());
        _Enemy_ENBar.SetValue(enemy.get()->GetStamina());

        _Player_HPBar.Draw();
        _Player_ENBar.Draw();

        _Enemy_HPBar.Draw();
        _Enemy_ENBar.Draw();

        _Grid.Draw();

		Healstamina();
		enemy->RecoverStamina(10);
	}
	EndBattle();
}




void BattleManager::Healstamina()
{
    // 스테미너 관리 Entity로 이관한다 하셔서 오류 방지를 위해 주석 처리 해놨습니다. 
    // player->AddStamina(15)
}

void BattleManager::ShowCard(std::vector<std::shared_ptr<Card>> card)//하빈
{
	//------------임시 테스트용--------------
	std::cout << "플레이어 카드 선택 :" << std::endl;
	for (int i = 0; i < card.size(); i++) {
		std::cout << i + 1 << ". " << card[i]->C_GetName() << " (cost: " << card[i]->C_GetCost() << ")" << std::endl;
		if (auto a = dynamic_cast<C_Attack*>(card[i].get())) {
			std::cout << "Power: " << a->A_GetATK() << std::endl;
			bool(*tmp)[3] = a->A_GetRange();
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					std::cout << (tmp[i][j] ? "O" : "X");
				}
				std::cout << std::endl;
			}
		}
	}
}

void BattleManager::ShowUI()//하빈
{
	// 플레이어와 적 사이의 거리를 계산
	int distanceX = std::abs(field.PlayerPositionX - field.EnemyPositionX);
	int distanceY = std::abs(field.PlayerPositionY - field.EnemyPositionY);

	// 3x3 범위 안에 있는지 확인
	bool isInAttackRange = (distanceX <= 1 && distanceY <= 1);

	//-------------임시 테스트용---------------
	std::cout << "==== 전투 UI ====\n";
	std::cout << player->GetName() << " HP: " << player->GetHP() << " Stamina: " << player->GetStamina()
		<< " | " << enemy->GetName() << " HP: " << enemy->GetHP() << " Stamina: " << enemy->GetStamina();

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

    bool IsSetEnemyCharacterWhenPlayerAttacked = false;

	// 플레이어 행동
	if (auto moveCard = dynamic_cast<C_Move*>(pCard.get())) //플레이어 이동
	{
		field.field_move(moveCard->M_GetX(), moveCard->M_GetY(), 1);
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, "@", Color::RED, Color::BLACK);
	}
	//체력 OR 스태미나 힐
	//적 이동
	else if (auto defenseCard = dynamic_cast<C_Guard*>(pCard.get())) //플레이어 방어
	{
        _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, "@", Color::RED, Color::BLACK);
		pCardDEF += defenseCard->G_GetDEF();
        _Log.PrintLog("방어가 " + std::to_string(defenseCard->G_GetDEF()) + "만큼 상승했다.");
		//std::cout << "방어가 " << defenseCard->G_GetDEF() << "만큼 상승했다." << std::endl;
	}
	//적 방어
	else if (auto attackCard = dynamic_cast<C_Attack*>(pCard.get())) //÷̾ 
	{
		if (player->GetStamina() < attackCard->C_GetCost()) {
            _Log.PrintLog("스태미나가 부족하다.");
			//std::cout << "스태미나가 부족하다." << std::endl;
		}
		else {
			std::vector<std::shared_ptr <Card>> *AllCardsList = GAME_MANAGER->GetAllCardsList();
			
			SOUND_MANAGER->PlaySE(SOUND_MANAGER->GetCardSEType(attackCard->C_GetName()));
			
			player->SetStamina(player->GetStamina() - attackCard->C_GetCost());
            _Grid.SetCharacter(field.PlayerPositionX, field.PlayerPositionY, "@", Color::RED, Color::BLACK);
            _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
            _Grid.PaintBlocks(field.PlayerPositionX, field.PlayerPositionY, attackCard->A_GetRange(), Color::RED);
            IsSetEnemyCharacterWhenPlayerAttacked = true;

			if (HitCheck(1, attackCard)) {
				int hitdamage = attackCard->A_GetATK() + player->GetATK() - enemy->GetDEF() - eCardDEF;
				if (hitdamage < 0) hitdamage = 0;
				enemy->TakeDamage(hitdamage);
                _Log.PrintLog("플레이어가 적에게 " + std::to_string(hitdamage) + "의 피해를 입혔다.");
				//std::cout << "플레이어가 적에게 " << hitdamage << "의 피해를 입혔다." << std::endl;
			}
			else {
                _Log.PrintLog("공격에 실패했다.");
				//std::cout << "공격에 실패했다." << std::endl;
			}
		}
	}

	// 적 행동
	if (auto moveCard = dynamic_cast<C_Move*>(eCard.get())) {
		field.field_move(moveCard->M_GetX(), moveCard->M_GetY(), 2);        
        if (!IsSetEnemyCharacterWhenPlayerAttacked) {
            _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
        }
        //_Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
		//std::cout << "적이 이동했습니다." << std::endl;
        _Log.PrintLog("적이 이동했습니다.");

	}
	else if (auto defenseCard = dynamic_cast<C_Guard*>(eCard.get())) {
		eCardDEF += defenseCard->G_GetDEF();
        if (!IsSetEnemyCharacterWhenPlayerAttacked) {
            _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
        }
        //_Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
		//std::cout << "적의 방어가 " << eCardDEF << "만큼 상승했다." << std::endl;
        _Log.PrintLog("적의 방어가 " + std::to_string(eCardDEF) + "만큼 상승했다.");
	}
	else if (auto attackCard = dynamic_cast<C_Attack*>(eCard.get())) {
		if (enemy->GetStamina() < attackCard->C_GetCost()) {
			//std::cout << "적의 스태미나가 부족합니다." << std::endl;
            _Log.PrintLog("적의 스태미나가 부족합니다.");
		}
		else {
            if (!IsSetEnemyCharacterWhenPlayerAttacked) {
                _Grid.SetCharacter(field.EnemyPositionX, field.EnemyPositionY, "#", Color::BLUE, Color::BLACK);
            }
            _Grid.PaintBlocks(field.EnemyPositionX, field.EnemyPositionY, attackCard->A_GetRange(), Color::BLUE);

			enemy->SetStamina(enemy->GetStamina() - attackCard->C_GetCost());

			if (HitCheck(2, attackCard)) {
				int hitdamage = attackCard->A_GetATK() + enemy->GetATK() - player->GetDEF() - pCardDEF;
				if (hitdamage < 0) hitdamage = 0;
				player->TakeDamage(hitdamage);
                _Log.PrintLog("적이 플레이어에게 " + std::to_string(hitdamage) + "의 피해를 입혔다.");
				//std::cout << "적이 플레이어에게 " << hitdamage << "의 피해를 입혔다." << std::endl;


			}
			else {
				//std::cout << "적의 공격이 실패했다." << std::endl;
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
	if (player->IsDead())
        _Log.PrintLog("플레이어 패배...");
	else {
        _Log.PrintLog("적 처치 성공!");
		player->AddEXP(enemy->getExp());
		enemy.reset();
	}
}

