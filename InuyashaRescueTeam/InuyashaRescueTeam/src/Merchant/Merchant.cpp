#include "Merchant\Merchant.h"
#include "Cards.h"
#include <iostream>
#include "GameManager/GameManager.h"
#include <windows.h>
#include "InputManager/InputManager.h"
#include <string>
#include "ImagePrinter.h"

#define FOREGROUND_WHITE      FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE // text color contains blue.

Merchant::Merchant()
{
	player = GAME_MANAGER->GetPlayer().lock();
	MakeList();
	index = 0;
	width = 24;
	gap = 1;
	height = ShopList.size() > InvenList.size() ? ShopList.size() : InvenList.size();
	bShopType = false;
	player->SetMoney(1000); // 테스트용 골드 부여
	OffsetX = 80;
	OffsetY = 10;
}

void Merchant::OpenShop()
{
	InputManager& IM = InputManager::GetInstance();
	KeyAction UserChoice;

	while (1)
	{
        DrawBackground();
		DrawShop();
		ShowList();
		DrawPlayerInven();
		ShowPlayerInvenList();
		ShowInforPanel();
		ShowCardInfo();
		UserChoice = IM.GetKeyAction(GameState::MERCHANT); // 유저 입력
		if (UserChoice == KeyAction::INVALID)
		{
			continue;
		}
		else if (UserChoice == KeyAction::QUIT) // Q 선택시 퇴장
		{
			break;
		}
		else if (UserChoice == KeyAction::PREV_ITEM)
		{
			if (index > 0)
			{
				--index;
			}
		}
		else if (UserChoice == KeyAction::NEXT_ITEM)
		{
			if (bShopType == false && index < ShopList.size() - 1)
			{
				++index;
			}
			else if (bShopType == true && index < InvenList.size() - 1)
			{
				++index;
			}
		}
		else if (UserChoice == KeyAction::SHOP_MERCHANT)
		{
			if (ShopList.empty())
			{
				continue;
			}
			bShopType = false;
			if (index > ShopList.size() - 1)
			{
				index = ShopList.size() - 1;
			}
		}
		else if (UserChoice == KeyAction::SHOP_PLAYER)
		{
			bShopType = true;
			if (index > InvenList.size() - 1)
			{
				index = InvenList.size() - 1;
			}
		}
		else if (UserChoice == KeyAction::SELECT)
		{
			TradeCard(index, bShopType);
		}
	}
	system("cls");
	std::cout << "상점을 닫습니다." << std::endl;
}

void Merchant::MakeList()
{
	std::vector<std::shared_ptr <Card>>* CardList = GAME_MANAGER->GetAllCardsList();
	for (int i = 0; i < 13; ++i) // 일단 전부 다 넣음. 나중에 몇개넣을지는 변수로 지정하는 것으로 변경 예정
	{
		ShopList.emplace_back((*CardList)[i], false);
	}
	InvenList = player->GetDeck();
}

void Merchant::DrawBackground()
{
	ImagePrinter image;
	image.DrawImage(KIKYO, 0, 0);
	image.DrawImage(INU, 140, 00);
}

void Merchant::DrawShop()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(0 + OffsetX), static_cast<short>(0 + OffsetY) });
	std::wstring msg = L"╔" + std::wstring(width - 2, L'═') + +L"╗";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
	for (int i = 0; i < height; ++i)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(0 + OffsetX), static_cast<short>(i + 1 + OffsetY) });
		std::cout << "║";
		if (i == index && bShopType == false)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		}
		std::cout << std::string(width - 2, ' ');
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		std::cout << "║";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(0 + OffsetX), static_cast<short>(height + 1 + OffsetY) });
	msg = L"╚" + std::wstring(width - 2, L'═') + +L"╝";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(width / 2 - 3 + OffsetX), static_cast <short>(0 + OffsetY) });
	msg = L"╡SHOP╞";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
}

void Merchant::ShowList()
{
	for (short i = 0; i < ShopList.size(); ++i)
	{
		if (i == index && bShopType == false)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(1 + OffsetX), static_cast<short>(i + 1 + OffsetY) });
		std::cout << " ○ " << ShopList[i].first->C_GetName();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
}

void Merchant::DrawPlayerInven()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	std::wstring msg = L"╔" + std::wstring(width - 2, L'═') + +L"╗\n";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + gap + OffsetX), static_cast<short>(0 + OffsetY) });
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
	for (int i = 0; i < height; ++i)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + gap + OffsetX), static_cast<short>(i + 1 + OffsetY) });
		std::cout << "║";
		if (i == index && bShopType == true)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		}
		std::cout << std::string(width - 2, ' ');
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		std::cout << "║";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + gap + OffsetX), static_cast<short>(height + 1 + OffsetY) });
	msg = L"╚" + std::wstring(width - 2, L'═') + +L"╝\n";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(width + gap + width / 2 - 4 + OffsetX), static_cast <short>(0 + OffsetY) });
	msg = L"╡PLAYER╞";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
}

void Merchant::ShowPlayerInvenList()
{
	for (short i = 0; i < InvenList.size(); ++i)
	{
		if (i == index && bShopType == true)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | BACKGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + gap + 1 + OffsetX), static_cast<short>(i + 1 + OffsetY) });
		std::cout << " ○ " << InvenList[i]->C_GetName();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
}

void Merchant::ShowInforPanel()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(0 + OffsetX), static_cast<short>(height + 2 + OffsetY) });
	std::wstring msg = L"╔" + std::wstring(width - 1, L'═') + L"╦" + std::wstring(width - 1, L'═')  +L"╗";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(0 + OffsetX), static_cast<short>(height + 3 + i + OffsetY) });
		std::cout << "║";
		std::cout << std::string(width - 1, ' ');
		std::cout << "║";
		std::cout << std::string(width - 1, ' ');
		std::cout << "║";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(0 + OffsetX), static_cast<short>(height + 7 + OffsetY) });
	msg = L"╚" + std::wstring(width - 1, L'═') + L"╩" + std::wstring(width - 1, L'═')  +L"╝\n";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + 6 + OffsetX), static_cast<short>(height + 2 + 3 + OffsetY) });
	msg = L"F를 눌러 구매";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + 6 + OffsetX), static_cast<short>(height + 2 + 4 + OffsetY) });
	msg = L"Q를 눌러 퇴장";
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
}

void Merchant::ShowCardInfo()
{
	if (bShopType)
	{
		TargetCard = InvenList[index];
	}
	else
	{
		TargetCard = ShopList[index].first;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 1 + OffsetY) });
	std::cout << " ○ " << TargetCard->C_GetName() << " ○ " << std::endl;
	if (std::shared_ptr<C_Move> moveCard = std::dynamic_pointer_cast<C_Move>(TargetCard))
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 2 + OffsetY) });
		std::cout << " ■ ■ ■ TYPE : Move" << std::endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 3 + OffsetY) });
		std::cout << " ■ ■ ■ Move : " << moveCard->M_GetDistance();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 4 + OffsetY) });
		std::cout << " ■ ■ ■ COST : " << moveCard->C_GetCost();
		if (moveCard->M_GetX())
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(4 + moveCard->M_GetX()*2 + OffsetX), static_cast<short>(height + 2 + 3 + OffsetY) });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
			std::cout << "■";
		}
		if (moveCard->M_GetY())
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(4 + OffsetX), static_cast<short>(height + 2 + 3 + moveCard->M_GetY() + OffsetY) });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
			std::cout << "■";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
	else if (std::shared_ptr<C_Guard> defenseCard = std::dynamic_pointer_cast<C_Guard>(TargetCard))
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 2 + OffsetY) });
		std::cout << " ■ ■ ■ TYPE : Guard" << std::endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 3 + OffsetY) });
		std::cout << " ■ ■ ■  DEF : " << defenseCard->G_GetDEF();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 4 + OffsetY) });
		std::cout << " ■ ■ ■ COST : " << defenseCard->C_GetCost();

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(4 + OffsetX), static_cast<short>(height + 2 + 3 + OffsetY) });
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		std::cout << "■";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
	else if (std::shared_ptr<C_Attack> attackCard = std::dynamic_pointer_cast<C_Attack>(TargetCard))
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 2 + OffsetY) });
		std::cout << " ■ ■ ■ TYPE : Attack" << std::endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 3 + OffsetY) });
		std::cout << " ■ ■ ■  ATK : " << attackCard->A_GetATK();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(1 + OffsetX), static_cast<short>(height + 2 + 4 + OffsetY) });
		std::cout << " ■ ■ ■ COST : " << attackCard->C_GetCost();
		
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (attackCard->A_GetRange()[i][j])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(2 + j*2 + OffsetX), static_cast<short>(height + 2 + 2 + i + OffsetY) });
					std::cout << "■";
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
			}
		}
	}
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + 8 + OffsetX), static_cast<short>(height + 2 + 1 + OffsetY) });
	std::cout << "가격: " << TargetCard->C_GetGold();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(width + 7 + OffsetX), static_cast<short>(height + 2 + 2 + OffsetY) });
	std::cout << "소지금: " << player->GetMoney();
}

void Merchant::TradeCard(short _index, bool _isPlayer)
{
	if (_isPlayer)
	{
		return;
	}
	if (player->GetMoney() < ShopList[_index].first->C_GetGold())
	{
		return;
	}
	else
	{
		player->SetMoney(player->GetMoney() - ShopList[_index].first->C_GetGold());
	}
	player->AddCard(ShopList[_index].first);
	ShopList.erase(ShopList.begin() + _index);
	InvenList = player->GetDeck();
	if (height < InvenList.size())
	{
		height = InvenList.size();
	}
	if (ShopList.empty())
	{
		bShopType = true;
	}
	else if (_index >= ShopList.size())
	{
		index = ShopList.size() - 1;
	}
    system("cls");
}
