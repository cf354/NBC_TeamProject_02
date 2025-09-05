#include "Merchant\Merchant.h"
#include <iostream>

Merchant::Merchant()
{
	// 테스트용 쇼핑 리스트
	ShopList = {
		{1, false},
		{2, false},
		{3, false},
		{4, false},
		{5, false},
		{6, false},
		{7, false},
		{8, false}
	};
}

void Merchant::OpenShop()
{
	char UserChoice;
	while (1)
	{
		system("cls");
		ShowList();
		std::cin >> UserChoice;
		if (std::cin.fail())
		{
			continue;
		}
		if (UserChoice < 'a' || UserChoice > 'z')
		{
			if (UserChoice == 'Q')
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

void Merchant::ShowList()
{
	char index = 'a';
	char Selected = '-';

	std::cout << "=====상점 리스트=====" << std::endl;
	for (auto it = ShopList.begin(); it != ShopList.end(); ++it)
	{
		(it->second) ? (Selected = '+') : (Selected = '-');
		std::cout << index++ << " " << Selected << " " << it->first << std::endl;
	}
}