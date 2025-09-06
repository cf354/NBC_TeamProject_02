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
	void ShowList(); // 판매할 물건을 보여줌

private:
	std::vector<std::pair<std::shared_ptr<class Card>, bool>> ShopList; // 출력할 물건 리스트, bool은 선택여부를 나타냄
};

