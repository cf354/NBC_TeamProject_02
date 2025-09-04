#pragma once
#include <string>

class Card
{
protected:
	std::string Name;
	int Cost;
	int Gold;

public:
	// ������ �� �Ҹ��� 
	Card(std::string n, int C, int G);
	virtual ~Card();

	// ��� �Լ� ����
	std::string C_GetName() const; 
	int C_GetCost() const;
	int C_GetGold() const;
};