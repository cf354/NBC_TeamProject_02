#include "BattleManager/BattleManager.h"
#include "Card/C_Move.h"
#include "Card/C_Attack.h"
#include "Card/C_Guard.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"

void BattleManager::StartBattle()
{
	std::cout << "전투 시작!\n";

	while (!player->IsDead() && !enemy->IsDead()) {
		field.field_print();
		ShowUI();
		std::shared_ptr<Card> pCard = PlayerTurn();

		// 적 턴 시작 시 플레이어와 적의 위치를 GetRandomCard 함수에 전달
		std::shared_ptr<Card> eCard = enemy->GetRandomCard(field.PlayerPositionX, field.PlayerPositionY, field.EnemyPositionX, field.EnemyPositionY);

		std::cout << enemy->GetName() << "이(가) [" << eCard->C_GetName() << "] 카드를 선택했다!\n";
		system("cls");
		Resolve(pCard, eCard, field);
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

void BattleManager::ShowCard(std::vector<std::shared_ptr<Card>> card)
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

void BattleManager::ShowUI()
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
	ShowCard(card);

	int choice = -1;
	while (true) {
		std::cout << "선택 (번호 입력): ";
		std::cin >> choice;

		// 입력 오류 방지
		if (std::cin.fail()) {
			std::cin.clear(); // 오류 플래그 클리어
			std::cin.ignore(1000, '\n'); // 잘못된 입력 버퍼 제거
			std::cout << "잘못된 입력입니다. 다시 입력하세요.\n";
			continue;
		}

		if (choice >= 1 && choice <= (int)card.size()) {
			break;
		}
		else {
			std::cout << "유효하지 않은 번호입니다. 다시 선택하세요.\n";
		}
	}

	return card[choice - 1];

}

void BattleManager::Resolve(std::shared_ptr<Card> pCard, std::shared_ptr<Card> eCard, BattleField& field)
{

	std::cout << "행동 실행!\n";
	int pCardDEF = 0;
	int eCardDEF = 0;
	// 플레이어 행동
	if (auto moveCard = dynamic_cast<C_Move*>(pCard.get())) //플레이어 이동
	{
		field.field_move(moveCard->M_GetX(), moveCard->M_GetY(), 1);
	}
	//적 이동
	else if (auto defenseCard = dynamic_cast<C_Guard*>(pCard.get())) //플레이어 방어
	{
		pCardDEF += defenseCard->G_GetDEF();
		std::cout << "방어가 " << defenseCard->G_GetDEF() << "만큼 상승했다." << std::endl;
	}
	//적 방어
	else if (auto attackCard = dynamic_cast<C_Attack*>(pCard.get())) //÷̾ 
	{
		if (player->GetStamina() < attackCard->C_GetCost()) {
			std::cout << "스태미나가 부족하다." << std::endl;
		}
		else {
			player->SetStamina(player->GetStamina() - attackCard->C_GetCost());
			if (HitCheck(1, attackCard)) {
				int hitdamage = attackCard->A_GetATK() + player->GetATK() - enemy->GetDEF() - eCardDEF;
				if (hitdamage < 0) hitdamage = 0;
				enemy->TakeDamage(hitdamage);
				std::cout << "플레이어가 적에게 " << hitdamage << "의 피해를 입혔다." << std::endl;
			}
			else {
				std::cout << "공격에 실패했다." << std::endl;
			}
		}
	}

	// 적 행동
	if (auto moveCard = dynamic_cast<C_Move*>(eCard.get())) {
		field.field_move(moveCard->M_GetX(), moveCard->M_GetY(), 2);
		std::cout << "적이 이동했습니다." << std::endl;
	}
	else if (auto defenseCard = dynamic_cast<C_Guard*>(eCard.get())) {
		eCardDEF += defenseCard->G_GetDEF();
		std::cout << "적의 방어가 " << eCardDEF << "만큼 상승했다." << std::endl;
	}
	else if (auto attackCard = dynamic_cast<C_Attack*>(eCard.get())) {
		if (enemy->GetStamina() < attackCard->C_GetCost()) {
			std::cout << "적의 스태미나가 부족합니다." << std::endl;
		}
		else {
			enemy->SetStamina(enemy->GetStamina() - attackCard->C_GetCost());
			if (HitCheck(2, attackCard)) {
				int hitdamage = attackCard->A_GetATK() + enemy->GetATK() - player->GetDEF() - pCardDEF;
				if (hitdamage < 0) hitdamage = 0;
				player->TakeDamage(hitdamage);
				std::cout << "적이 플레이어에게 " << hitdamage << "의 피해를 입혔다." << std::endl;
			}
			else {
				std::cout << "적의 공격이 실패했다." << std::endl;
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
		std::cout << "플레이어 패배...\n";
	else {
		std::cout << "적 처치 성공!\n";
		player->AddEXP(enemy->getExp());
		enemy.reset();
	}
}

