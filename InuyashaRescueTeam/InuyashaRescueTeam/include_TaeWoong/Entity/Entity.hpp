#pragma once // ��� ���� �ߺ� ���� ����
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

public:
    // ������ �� �Ҹ���
    Entity(const std::string& name, int level, int hp, int stamina, int atk, int def);
    virtual ~Entity();

    // �ǰ� �� ������ ���
    void TakeDamage(int damage);

    // ���� ��ȯ (Getter)
    int GetLv() const;
    int GetHP() const;
    int GetStamina() const;
    int GetATK() const;
    int GetDEF() const;
    std::string GetName() const;

    // ���� ���� (Setter) 
    void SetHP(int hp);
    void SetStamina(int stamina);
    
};