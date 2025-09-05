#include "Merchant\Merchant.h"
#include "Cards.h"
#include <iostream>
#include "GameManager/GameManager.h"

Merchant::Merchant()
{
	MakeList();
}

void Merchant::OpenShop()
{
	char UserChoice;
	while (1)
	{
		system("cls");
		ShowList();
		std::cin >> UserChoice; // 유저 입력
		if (std::cin.fail())
		{
			continue;
		}
		if (UserChoice < 'a' || UserChoice > 'z') // a~z까지 아이템 인덱스를 골라서 선택하기
		{
			if (UserChoice == 'Q') // Q 선택시 퇴장
			{
				break;
			}
			continue;
		}
		if (UserChoice - 'a' < ShopList.size())
		{
			ShopList[UserChoice - 'a'].second = !(ShopList[UserChoice - 'a'].second);
		}
	}
	system("cls");
	std::cout << "상점을 닫습니다." << std::endl;
}

void Merchant::MakeList()
{
	GameManager game;
	std::vector<std::shared_ptr <Card>>* CardList = game.GetAllCardsList();
	for (int i = 0; i < 13; ++i) // 일단 전부 다 넣음. 나중에 몇개넣을지는 변수로 지정하는 것으로 변경 예정
	{
		ShopList.emplace_back((*CardList)[i], false);
	}
}

void Merchant::ShowList()
{
	char index = 'a';
	char Selected = '-';

	std::cout << "=====상점 리스트=====" << std::endl;
	for (auto it = ShopList.begin(); it != ShopList.end(); ++it)
	{
		(it->second) ? (Selected = '+') : (Selected = '-');
		std::cout << index++ << " " << Selected << " " << it->first->C_GetName() << std::endl;
	}
	std::cout << "=====================" << std::endl;
}