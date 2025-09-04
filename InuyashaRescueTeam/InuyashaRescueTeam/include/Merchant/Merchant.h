#pragma once
#include <vector>
#include <utility>

// 상인
class Merchant 
{
public:
	Merchant();
	void OpenShop(); // 플레이어와 상호작용할때 사용

private:
	void ShowList(); // 판매할 물건을 보여줌

private:
	std::vector<std::pair<int, bool>> ShopList; // 출력할 물건 리스트, int대신 Card로 바꿀 예정, bool은 선택여부를 나타냄
};

