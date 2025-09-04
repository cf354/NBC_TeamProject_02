#pragma once
#include "Entity\Entity.h"
#include <iostream>
#include <vector>
#include "Card\Card.h"

class Enemy : public Entity {
private:
	int drop_money;
	int drop_exp;
	std::vector<std::shared_ptr<Card>> deck;

public:
	Enemy(std::string n, int lv, int h, int s, int a, int d, int dm, int de)
		: Entity(n, lv, h, s, a, d), drop_money(dm), drop_exp(de) {
	}
	int getExp() { return drop_exp; }
	int getmoney() { return drop_money; }

	void AddCard(const std::shared_ptr<Card>& c) { deck.push_back(c); }
	std::vector<std::shared_ptr<Card>>& GetCards() { return deck; }

	~Enemy() {};

	//----------------임시 테스트용----------------
	std::shared_ptr<Card> GetRandomCard() {
		int idx = rand() % deck.size();
		return deck[idx];
	}
	
};


