#include "Entity\Entity.h"

// 생성자
Entity::Entity(const std::string& name, int level, int hp, int stamina, int atk, int def, const char* spritefilefath)
    : Name(name), Level(level), ATK(atk), DEF(def), SpriteFileFath(spritefilefath)
{
    // 생성 시 넘겨준 값이 곧 최대치
    MAXHP = hp;
    MAXStamina = stamina;

    // 현재 체력/스태미나를 최대치 범위 내로 보정
    HP = (hp > MAXHP) ? MAXHP : hp;
    if (HP < 0) HP = 0;

    Stamina = (stamina > MAXStamina) ? MAXStamina : stamina;
    if (Stamina < 0) Stamina = 0;
}

// 소멸자 
Entity::~Entity() {}

// 피격 시 데미지 계산
void Entity::TakeDamage(int damage)
{
    HP -= damage;

    if (HP < 0) { HP = 0; }

    //std::cout << Name << "이(가) " << damage << "의 데미지를 입었습니다. 현재 HP: " << HP << std::endl;
}

// 정보 반환 
int Entity::GetLv() const { return Level; }
int Entity::GetHP() const { return HP; }
int Entity::GetStamina() const { return Stamina; }
int Entity::GetATK() const { return ATK; }
int Entity::GetDEF() const { return DEF; }
std::string Entity::GetName() const { return Name; }
int Entity::GetMAXHP() const { return MAXHP; }
int Entity::GetMAXStamina() const { return MAXStamina; }
const char* Entity::GetSpriteFileFath() const{ return SpriteFileFath; }

// 정보 설정 
void Entity::SetHP(int hp)
{
    this->HP = hp;
}

void Entity::SetMaxHP(int hp)
{
    this->MAXHP = hp;
}

void Entity::SetStamina(int stamina)
{
    this->Stamina = stamina;
}

void Entity::SetMaxStamina(int mSP)
{
    this->MAXStamina = mSP;
}

void Entity::RecoverStamina(int amount)
{
    Stamina = std::min(Stamina + amount, MAXStamina);
}

bool Entity::IsDead()
{
    if (HP > 0) {
        return false;
    }
    else {
        return true;
    }
}