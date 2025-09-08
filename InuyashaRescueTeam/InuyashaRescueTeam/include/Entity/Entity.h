#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class Entity {
protected:
    std::string Name;
    int Level;
    int HP;
    int Stamina;
    int ATK;
    int DEF;

    int MAXHP;
    int MAXStamina;

public:
    // 생성자 및 소멸자
    Entity(const std::string& name, int level, int hp, int stamina, int atk, int def);
    virtual ~Entity();

    // 피격 시 데미지 계산
    void TakeDamage(int damage);

    // 정보 반환 (Getter)
    int GetLv() const;
    int GetHP() const;
    int GetStamina() const;
    int GetATK() const;
    int GetDEF() const;
    std::string GetName() const;

    int GetMAXHP() const;
    int GetMAXStamina() const;

    // 정보 설정 (Setter)
    void SetHP(int hp);
    void SetMaxHP(int mHP);
    void SetStamina(int stamina);
    void SetMaxStamina(int mSP);

    void RecoverStamina(int amount) {
        Stamina = std::min(Stamina + amount, MAXStamina);
    }

    bool IsDead();
};