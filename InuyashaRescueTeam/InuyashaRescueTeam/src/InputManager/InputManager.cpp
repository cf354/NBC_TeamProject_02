#include "InputManager/InputManager.h"

// static 멤버 변수 초기화
InputManager& InputManager::GetInstance()
{
    static InputManager instance; // 싱글톤 초기화
    return instance;
}

KeyAction InputManager::GetKeyAction(GameState currentState)
{
    int keyInput = _getch();

    // 상황에 따른 입력 분기
    switch (currentState)
    {
        // 필드(FIELD) 상태 - 맵 이동 중 키 입력 처리
    case GameState::FIELD:
    {
        switch (keyInput)
        {
        case 'e': case 'E': return KeyAction::GAIN_EXP;
        case 'q': case 'Q': return KeyAction::QUIT;
        case 's': case 'S': return KeyAction::SHOW_CARDS;
        }
        if (keyInput == 224)
        { // 방향키
            keyInput = _getch();
            switch (keyInput)
            {
            case 72: return KeyAction::MOVE_UP;
            case 80: return KeyAction::MOVE_DOWN;
            case 75: return KeyAction::MOVE_LEFT;
            case 77: return KeyAction::MOVE_RIGHT;
            }
        }
        break; // FIELD 상태 처리 끝
    }

    // 상점(MERCHANT) 상태 - 맵 이동 중 키 입력 처리
    case GameState::MERCHANT:
    {
        switch (keyInput)
        { // 상점에 필요한 기능 추가해주세요.
          // 카드 구매, 판매 등등
        case 'q': case 'Q': return KeyAction::QUIT; // 상점 나가기
        case 'f': case 'F': return KeyAction::SELECT; // 물건 선택
        }
        if (keyInput == 224) { // 방향키로 아이템 선택
            keyInput = _getch();
            switch (keyInput)
            {
                // "InputManager.h"의 "enum class KeyAction" 필요한 액션 추가 후 사용
                 case 72: return KeyAction::PREV_ITEM;
                 case 80: return KeyAction::NEXT_ITEM;
                 case 75: return KeyAction::SHOP_MERCHANT;
                 case 77: return KeyAction::SHOP_PLAYER;
            }
        }
        break; // MERCHANT 상태 처리 끝
    }

    // 전투(BATTLE) 상태 - 맵 이동 중 키 입력 처리
    case GameState::BATTLE:
    {
        switch (keyInput)
        { // 전투에 필요한 기능 추가해주세요.
        // "InputManager.h"의 "enum class KeyAction" 필요한 액션 추가 후 사용
        // case 'a': case 'A': return KeyAction::ATTACK; // (예시)
        // case 'd': case 'D': return KeyAction::DEFEND; // (예시)
        // case 's': case 'S': return KeyAction::SHOW_CARDS; // (예시)
        }
        break; // BATTLE 상태 처리 끝
    }
    }

    return KeyAction::INVALID; // 유효 키 외 입력 방지
}