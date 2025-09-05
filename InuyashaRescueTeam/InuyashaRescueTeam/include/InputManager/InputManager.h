#pragma once
#include <conio.h> // _getch() 사용

// 입력 행동 정의 (기능 추가) - 마음껏 바꿔주세요
enum class KeyAction
{
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    ENTER_MERCHANT,     // 상점 입장    - 테스트용으로 임의로 넣은 것 입니다. 뺴도 되요
    QUIT_MERCHANT,      // 상점 퇴장    - 테스트용으로 임의로 넣은 것 입니다. 뺴도 되요
    ENTER_BATTLE,       // 전투 입장    - 테스트용으로 임의로 넣은 것 입니다. 뺴도 되요
    QUIT_BATTLE,        // 전투 퇴장    - 테스트용으로 임의로 넣은 것 입니다. 뺴도 되요
    SHOW_CARDS,         // 카드 출력    - 테스트용으로 임의로 넣은 것 입니다. 뺴도 되요
    GAIN_EXP,           // 경험치 상승  - 테스트용으로 임의로 넣은 것 입니다. 뺴도 되요
    QUIT,
    INVALID             // 유효하지 않은 키
};

// 게임 상황 정의
enum class GameState
{
    FIELD,          // 필드 이동 
    MERCHANT,       // 상점 이용 
    BATTLE          // 전투 상태
};

class InputManager
{
private:
    // 생성자 및 소멸자 - 싱글톤 패턴 적용(maybe...)
    InputManager() {}
    ~InputManager() {}

    // 복사 및 대입 방지
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

public:
    // 싱글톤 인스턴스를 가져오기 (static 선언 - 단일 인스턴스 이용)
    static InputManager& GetInstance();

    // 키 입력 (KeyAction) 변환 - State 인자를 받아 입력 구분
    KeyAction GetKeyAction(GameState currentState);
};