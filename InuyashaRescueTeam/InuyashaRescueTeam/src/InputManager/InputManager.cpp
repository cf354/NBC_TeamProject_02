#include "InputManager.h"

// static 멤버 변수 초기화
InputManager& InputManager::GetInstance()
{
    static InputManager instance; // 싱글톤 초기화
    return instance;
}

KeyAction InputManager::GetKeyAction()
{
    int keyInput = _getch();

    // 일반 키 입력 처리 (임의 지정 - CASE문 변경 가능)
    switch (keyInput)
    {
    case 'e': case 'E': // E 입력
        return KeyAction::GAIN_EXP;
    case 'q': case 'Q': // Q 입력
        return KeyAction::QUIT;
    case 's': case 'S': // S 입력
        return KeyAction::SHOW_CARDS;
    }

    // 방향키 입력 처리 (224로 시작하는 특수 키)
    if (keyInput == 224) {
        keyInput = _getch(); // 224 이후 방향키 값
        switch (keyInput) {
        case 72: return KeyAction::MOVE_UP;
        case 80: return KeyAction::MOVE_DOWN;
        case 75: return KeyAction::MOVE_LEFT;
        case 77: return KeyAction::MOVE_RIGHT;
        }
    }

    return KeyAction::INVALID; // 유효 키 외 입력 방지
}