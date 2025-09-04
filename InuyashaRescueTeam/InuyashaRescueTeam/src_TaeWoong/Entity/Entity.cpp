#include "Entity.hpp"

// ������ 
Entity::Entity(const std::string& name, int level, int hp, int stamina, int atk, int def)
    : Name(name), Level(level), HP(hp), Stamina(stamina), ATK(atk), DEF(def) {
}

// �Ҹ��� 
Entity::~Entity() {}

// �ǰ� �� ������ ���
void Entity::TakeDamage(int damage)
{
    HP -= damage;

    if (HP < 0) { HP = 0; }

    std::cout << Name << "��(��) " << damage << "�� �������� �Ծ����ϴ�. ���� HP: " << HP << std::endl;
}

// ���� ��ȯ 
int Entity::GetLv() const { return Level; }
int Entity::GetHP() const { return HP; }
int Entity::GetStamina() const { return Stamina; }
int Entity::GetATK() const { return ATK; }
int Entity::GetDEF() const { return DEF; }
std::string Entity::GetName() const { return Name; }

// ���� ���� 
void Entity::SetHP(int hp)
{
    this->HP = hp;
}

void Entity::SetStamina(int stamina)
{
    this->Stamina = stamina;
}