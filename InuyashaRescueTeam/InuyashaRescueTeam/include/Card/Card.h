#pragma once
#include <string>

class Card
{

protected:
	std::string Name = "tmp";
	int Cost = 0;
	int Gold = 0;

public:

	Card(std::string n, int C, int G) { Name = n; Cost = C; Gold = G; }
	std::string C_GetName() {
		return Name;
	}
	int C_GetCost() {
		return Cost;
	}
	int C_GetGold() {
		return Gold;
	}

	virtual ~Card() {};

};

