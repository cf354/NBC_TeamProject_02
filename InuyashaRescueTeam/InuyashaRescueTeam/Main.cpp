#include <iostream>
#include <vector>
#include <string>
#include "Cards.h"
#include "Entities.h"
#include "battlefield\battlefield.h"
#include "BattleManager\BattleManager.h"
#include "GameManager\GameManager.h"
#include <windows.h>
//#include "Merchant\Merchant.h" 상점 테스트용
#include "Map/MapManager.h"



int main() {
    srand((unsigned int)time(nullptr)); // 랜덤 시드 적카드 뽑기때문에 임시로..
    SetConsoleOutputCP(CP_UTF8);
    // 또는 wide 출력: _setmode(_fileno(stdout), _O_U16TEXT);
    std::cout << "--------------------안녕------------------------" << std::endl;

    // 게임매니저 사용할 때, GAME_MANAGER-> 로 접근
    GAME_MANAGER->Init();

    while (true)
    {
        GAME_MANAGER->Update();
    }
    //// 상점 테스트 부분
    //Merchant* test = new Merchant();
    //test->OpenShop();

    return 0;
}
