#pragma once
#include <string>

class Entity {
protected:
	std::string name;
	int level;
	int hp;
	int stamina;
	int atk;
	int def;
	int MAXstamina;
	int MAXhp;

public:
	Entity(std::string n, int lv, int h, int s, int a, int d)
		: name(n), level(lv), hp(h), stamina(s), atk(a), def(d), MAXhp(h), MAXstamina(s) {
	}

	

	int GetHP() const { return hp; }
	int GetStamina() const { return stamina; }
	int GetAttack() const { return atk; }
	int GetDEF()const { return def; }
	std::string GetName() const { return name; }
	void SetStamina(int n);
	void SetHP(int n);
	void SetDEF(int n) { def = n; }
	void SetATK(int n) { atk = n; }
	void SetMAXstamina(int n) { MAXstamina = n; }
	void SetMAXhp(int n) { MAXhp = n; }


	void TakeDamage(int dmg);

	bool IsDead() const { return hp <= 0; }

	virtual ~Entity() {}
};



