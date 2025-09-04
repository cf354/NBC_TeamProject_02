#include <iostream>
#include <vector>
#include <string>
#include "Cards.h"
#include "Entities.h"
#include "battlefield\battlefield.h"
#include "BattleManager\BattleManager.h"
#include "GameManager\GameManager.h"



int main() {
    srand((unsigned int)time(nullptr)); // 랜덤 시드 적카드 뽑기때문에 임시로..
    GameManager game;
    game.Run();
    return 0;
}
