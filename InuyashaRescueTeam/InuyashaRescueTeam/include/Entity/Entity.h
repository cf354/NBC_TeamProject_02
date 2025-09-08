#pragma once // 헤더 파일 중복 포함 방지
#include <iostream>
#include <string>

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
    void SetStamina(int stamina);

    void RecoverStamina(int amount) {
        SetStamina(GetStamina() + amount);
    }
    
    bool IsDead();
};