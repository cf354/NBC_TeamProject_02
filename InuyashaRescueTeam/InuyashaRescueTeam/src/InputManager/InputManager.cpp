#include "InputManager/InputManager.h"

// static 멤버 변수 초기화
InputManager& InputManager::GetInstance()
{
    static InputManager instance; // 싱글톤 초기화
    return instance;
}

// 입력 버퍼 비우기
void InputManager::FlushInputBuffer()
{
    // 버퍼에 키 입력이 없을 때까지 계속해서 키를 읽어와서 버리기
    while (_kbhit())
    {
        _getch();
    }
}

KeyAction InputManager::GetKeyAction(GameState currentState)
{
    // --- 단발성 키 입력 감지 ---
    // _kbhit() - 키보드 버퍼 눌린 키 확인
    if (_kbhit())
    {
        int keyInput = _getch(); // 버퍼 키 가져오기

        switch (currentState)
        {
        case GameState::FIELD:
            switch (keyInput)
            {
                /*case 'e': case 'E': return KeyAction::GAIN_EXP;
                case 'q': case 'Q': return KeyAction::QUIT;
                case 's': case 'S': return KeyAction::SHOW_CARDS;*/
                case 'i': return KeyAction::INVENTORY;
            }
            break;

            // 상점(MERCHANT) 상태 - 맵 이동 중 키 입력 처리
        case GameState::MERCHANT:
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
            case GameState::BATTLE:
                switch (keyInput)
                {
                    /*case 'a': case 'A': return KeyAction::ATTACK;
                    case 'd': case 'D': return KeyAction::DEFEND;
                    case 's': case 'S': return KeyAction::SHOW_CARDS;
                    case 'r': case 'R': return KeyAction::FLEE;*/
                }
                break;
            }
        }

        return KeyAction::INVALID; // 아무 키도 눌리지 않았거나 유효하지 않은 키

}