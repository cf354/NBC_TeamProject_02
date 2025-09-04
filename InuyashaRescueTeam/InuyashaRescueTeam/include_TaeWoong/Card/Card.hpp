#pragma once
#include <string>

class Card
{
protected:
	std::string Name;
	int Cost;
	int Gold;

public:
	// 생성자 및 소멸자 
	Card(std::string n, int C, int G);
	virtual ~Card();

	// 멤버 함수 선언
	std::string C_GetName() const; 
	int C_GetCost() const;
	int C_GetGold() const;
};