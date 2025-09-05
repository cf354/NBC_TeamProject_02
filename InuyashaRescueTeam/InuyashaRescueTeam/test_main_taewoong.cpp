//#include <iostream>
//#include <vector>
//#include <string>
//#include "Cards.h"
//#include "Entities.h"
//#include "battlefield\battlefield.h"
//#include "BattleManager\BattleManager.h"
//#include "GameManager\GameManager.h"
//#include <windows.h>
//#include "InputManager\InputManager.h" // InputManager 헤더 추가
//#include <memory>
//
//int main()
//{
//    Player player("Hero", 1, 100, 50, 10, 5);
//    hideCursor();
//
//    // 임의적 카드 추가 - 마음껏 수정
//    bool attackRange[3][3] = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} };
//    player.AddCard(std::make_shared<C_Attack>("강타", 2, 0, 10, attackRange));
//    player.AddCard(std::make_shared<C_Move>("전진", 1, 0, 1, 0, 1));
//    player.AddCard(std::make_shared<C_Guard>("방패 막기", 1, 0, 5));
//
//    // 현재 게임 상태를 관리하는 변수
//    GameState currentState = GameState::FIELD;
//    bool isGameRunning = true;
//
//    while (isGameRunning)
//    {
//        // 상황에 따른 화면 출력 분기
//        setCursorPosition(0, 0); // 커서 위치 맞추기
//        switch (currentState)
//        {
//        case GameState::FIELD:
//            // 필드 출력에 대한 예시입니다. 마음껏 변경
//            // std::cout << "***** 필드 *****" << std::endl;
//            // std::cout << "이동:방향키, 카드:S, 상점:M, 종료:Q" << std::endl;
//            // player.PrintStatus();
//            break;
//        case GameState::MERCHANT:
//            // 상점 출력에 대한 예시입니다. 마음껏 변경
//            // std::cout << "***** 상점 *****" << std::endl;
//            // std::cout << "아이템 선택:방향키, 구매:B, 나가기:Q" << std::endl;
//            // ... (상점 UI 출력) ...
//            break;
//        case GameState::BATTLE:
//            // 전투 출력에 대한 예시입니다. 마음껏 변경
//            // std::cout << "***** 전투 *****" << std::endl;
//            // std::cout << "공격:A, 방어:D, 카드:S, 포기:Q" << std::endl;
//            // ... (전투 UI 출력) ...
//            break;
//        }
//
//        // 현재 상태(currentState) 기반으로 입력 처리 (Input Manager 생성)
//        KeyAction action = InputManager::GetInstance().GetKeyAction(currentState);
//
//        // 입력에 따른 상태 업데이트
//        if (currentState == GameState::FIELD) // 기본 - 필드 이동 상태
//        {
//            switch (action)
//            {
//            case KeyAction::MOVE_UP:    player.Move(Direction::UP); break;
//            case KeyAction::MOVE_DOWN:  player.Move(Direction::DOWN); break;
//            case KeyAction::MOVE_LEFT:  player.Move(Direction::LEFT); break;
//            case KeyAction::MOVE_RIGHT: player.Move(Direction::RIGHT); break;
//            // 상점 입장 상호작용
//            case KeyAction::ENTER_MERCHANT:
//                currentState = GameState::MERCHANT; // 상태 변경
//                // ... 상점 기능 구현 ...
//                // 카드 구매, 판매 등등
//                break;
//            // 전투 입장 상호작용
//            case KeyAction::ENTER_BATTLE:
//                currentState = GameState::BATTLE;   // 상태 변경
//                // ... 전투 기능 구현 ...
//                break;
//            case KeyAction::QUIT:
//                isGameRunning = false;
//                break;
//            }
//        }
//        else if (currentState == GameState::MERCHANT) // 상점 이용 중 입력
//        {
//            // ... (상점에서의 행동 처리) ...
//            // CASE 혹은 IF문 사용 (위는 CASE 예시, 아래는 IF문 예시)
//            if (action == KeyAction::QUIT_MERCHANT) // 상점 종료 시
//            {
//                currentState = GameState::FIELD; // 필드 상태로 변경
//            }
//        }
//        else if (currentState == GameState::BATTLE) // 전투 진행 중 입력
//        {
//            // ... (전투에서의 행동 처리) ...
//            if (action == KeyAction::QUIT_BATTLE) // 전투 종료 시
//            {
//                currentState = GameState::FIELD; // 필드 상태로 변경
//            }
//        }
//    }
//    std::cout << "게임을 종료합니다." << std::endl;
//    return 0;
//}