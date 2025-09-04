#include "Card.hpp"

// »ı¼ºÀÚ
Card::Card(std::string n, int C, int G) : Name(n), Cost(C), Gold(G) 
{ }

// ¼Ò¸êÀÚ 
Card::~Card() { }

// ¸â¹ö ÇÔ¼ö 
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