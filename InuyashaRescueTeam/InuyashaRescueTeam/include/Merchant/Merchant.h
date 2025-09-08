#pragma once
#include <vector>
#include <utility>
#include <memory>

// 상인
class Merchant 
{
public:
	Merchant();
	void OpenShop(); // 플레이어와 상호작용할때 사용

private:
	void MakeList(); // 판매할 물건 리스트 생성
	void DrawBackground(); // 배경 그리기
	void DrawShop(); // 판매 창 그리기
	void ShowList(); // 판매할 물건을 보여줌
	void DrawPlayerInven();
	void ShowPlayerInvenList();
	void ShowInforPanel();
	void ShowCardInfo();
	void TradeCard(short _index, bool _isPlayer);

private:
	std::vector<std::pair<std::shared_ptr<class Card>, bool>> ShopList; // 출력할 물건 리스트, bool은 선택여부를 나타냄
	std::vector<std::shared_ptr<Card>> InvenList; // 플레이어 덱 정보
	short OffsetX = 0;
	short OffsetY = 0;
	short index = 0;
	short width = 0;
	short height = 0;
	short gap = 0; // 상점 창과 플레이어 창의 간격
	bool bShopType = false;
	std::shared_ptr<class Player> player;
	std::shared_ptr<Card> TargetCard;
};

