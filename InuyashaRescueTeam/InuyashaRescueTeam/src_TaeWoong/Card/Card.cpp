#include "Card.hpp"

// ������
Card::Card(std::string n, int C, int G) : Name(n), Cost(C), Gold(G) 
{ }

// �Ҹ��� 
Card::~Card() { }

// ��� �Լ� 
std::string Card::C_GetName() const
{
	return Name;
}

int Card::C_GetCost() const
{
	return Cost;
}

int Card::C_GetGold() const
{
	return Gold;
}