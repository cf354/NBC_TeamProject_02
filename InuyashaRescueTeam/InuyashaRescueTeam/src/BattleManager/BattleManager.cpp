#include "BattleManager\BattleManager.h"

void BattleManager::StartBattle()
{
    std::cout << "���� ����!\n";

    while (!player->IsDead() && !enemy->IsDead()) {
        field.field_print();
        ShowUI();
        std::shared_ptr<Card> pCard = PlayerTurn();
        std::shared_ptr<Card> eCard = enemy->GetRandomCard();

        std::cout << enemy->GetName() << "��(��) [" << eCard->C_GetName() << "] ī�带 �����ߴ�!\n";//�����ؾ���
        system("cls");
        Resolve(pCard, eCard, field);
        Healstamina();

    }
    EndBattle();
}

void BattleManager::Healstamina()
{
    player->SetStamina(player->GetStamina() + player->getTurnHealStamina());

    //-------------�ӽ� �׽�Ʈ��-------------
    std::cout << player->getTurnHealStamina() << " ��ŭ ���¹̳� ȸ��!" << std::endl;
}

void BattleManager::ShowCard(std::vector<std::shared_ptr<Card>> card)
{
    //------------�ӽ� �׽�Ʈ��--------------
    std::cout << "�÷��̾� ī�� ���� :" << std::endl;
    for (int i = 0; i < card.size(); i++) {
        std::cout << i + 1 << ". " << card[i]->C_GetName() << " (cost: " << card[i]->C_GetCost() << ")" << std::endl;
        if (auto a = dynamic_cast<C_Attack*>(card[i].get())) {
            std::cout << "Power: " << a->A_GetATK() << std::endl;
            bool (*tmp)[3] = a->A_GetRange();
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
    //-------------�ӽ� �׽�Ʈ��---------------
    std::cout << "==== ���� UI ====\n";
    std::cout << player->GetName() << " HP: " << player->GetHP() << " Stamina: " << player->GetStamina()
        << " | " << enemy->GetName() << " HP: " << enemy->GetHP() << "\n";
}

std::shared_ptr<Card> BattleManager::PlayerTurn()
{
    std::vector<std::shared_ptr<Card>> card = player->GetCards();
    ShowCard(card);

    int choice = -1;
    while (true) {
        std::cout << "���� (��ȣ �Է�): ";
        std::cin >> choice;

        // �Է� ���� ����
        if (std::cin.fail()) {
            std::cin.clear(); // ���� �÷��� Ŭ����
            std::cin.ignore(1000, '\n'); // �߸��� �Է� ���� ����
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n";
            continue;
        }

        if (choice >= 1 && choice <= (int)card.size()) {
            break;
        }
        else {
            std::cout << "��ȿ���� ���� ��ȣ�Դϴ�. �ٽ� �����ϼ���.\n";
        }
    }

    return card[choice - 1];
}

void BattleManager::Resolve(std::shared_ptr<Card> pCard, std::shared_ptr<Card> eCard, BattleField& field)
{
    std::cout << "�ൿ ����!\n";
    int pCardDEF = 0;
    int eCardDEF = 0;
    // �÷��̾� �ൿ
    if (auto moveCard = dynamic_cast<C_Move*>(pCard.get())) //�÷��̾� �̵�
    {
        field.field_move(moveCard->M_GetX(), moveCard->M_GetY());
    }
    //�� �̵�
    else if (auto defenseCard = dynamic_cast<C_Guard*>(pCard.get())) //�÷��̾� ���
    {
        pCardDEF += defenseCard->G_GetDEF();
        std::cout << "�� " << defenseCard->G_GetDEF() << "��ŭ ����ߴ�." << std::endl;
    }
    //�� ���
    else if (auto attackCard = dynamic_cast<C_Attack*>(pCard.get())) //�÷��̾� ����
    {
        if (player->GetStamina() < attackCard->C_GetCost()) {
            std::cout << "���¹̳��� �����ϴ�." << std::endl;
        }
        else {
            player->SetStamina(player->GetStamina() - attackCard->C_GetCost());
            if (HitCheck(1, attackCard)) {
                int hitdamage = attackCard->A_GetATK() + player->GetAttack() - enemy->GetDEF() - eCardDEF;
                enemy->TakeDamage(hitdamage);
                std::cout << "�÷��̾ ������ " << hitdamage << "�� ���ظ� ������." << std::endl;
            }
            else {
                std::cout << "���ݿ� �����ߴ�." << std::endl;
            }
        }
    }


    // �� ����

}

bool BattleManager::HitCheck(int Entity, C_Attack* card)
{
    int RposX = field.PlayerPositionX - field.EnemyPositionX;
    int RposY = field.PlayerPositionY - field.EnemyPositionY;
    if (RposX > 1 || RposX < -1 || RposY>1 || RposY < -1) {
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
        std::cout << "�÷��̾� �й�...\n";
    else {
        std::cout << "�� óġ ����!\n";
        player->setExp(player->getExp() + enemy->getExp());
        player->setMoney(player->getMoney() + enemy->getmoney());
        enemy.reset();
    }

}
