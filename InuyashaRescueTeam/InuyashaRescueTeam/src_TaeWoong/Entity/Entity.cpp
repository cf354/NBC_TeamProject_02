#include "Entity.hpp"

// 생성자 
Entity::Entity(const std::string& name, int level, int hp, int stamina, int atk, int def)
    : Name(name), Level(level), HP(hp), Stamina(stamina), ATK(atk), DEF(def) {
}

// 소멸자 
Entity::~Entity() {}

// 피격 시 데미지 계산
void Entity::TakeDamage(int damage)
{
    HP -= damage;

    if (HP < 0) { HP = 0; }

    std::cout << Name << "이(가) " << damage << "의 데미지를 입었습니다. 현재 HP: " << HP << std::endl;
}

// 정보 반환 
int Entity::GetLv() const { return Level; }
int Entity::GetHP() const { return HP; }
int Entity::GetStamina() const { return Stamina; }
int Entity::GetATK() const { return ATK; }
int Entity::GetDEF() const { return DEF; }
std::string Entity::GetName() const { return Name; }

// 정보 설정 
void Entity::SetHP(int hp)
{
    this->HP = hp;
}

void Entity::SetStamina(int stamina)
{
    this->Stamina = stamina;
}