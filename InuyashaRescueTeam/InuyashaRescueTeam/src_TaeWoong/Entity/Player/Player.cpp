#include "Player.hpp"
#include "Card.hpp"     // 카드 헤더 포함
#include "C_Attack.hpp" // 카드 헤더 포함
#include "C_Guard.hpp"  // 카드 헤더 포함
#include "C_Move.hpp"   // 카드 헤더 포함
#include <iostream>
#include <typeinfo> // dynamic_cast 사용을 위해 추가

// 커서 위치를 (x, y)로 이동시키는 함수
void setCursorPosition(int x, int y) 
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 커서를 숨기는 함수
void hideCursor() 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; // 커서를 보이지 않게 설정
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 현재 커서 Y 좌표(줄 번호) 반환 함수
int getCurrentCursorLine() 
{
    // 콘솔 화면 정보를 담을 구조체를 선언
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // 콘솔 화면 정보 가져오기
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
    {
        // 구조체 안의 커서 위치(dwCursorPosition)에서 Y값 반환
        return csbi.dwCursorPosition.Y;
    }
    return -1; // 에러 발생 시 -1 반환
}

// 특정 줄 지우기 함수
void clearLine(int lineNumber) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD startCoords = { 0, (SHORT)lineNumber };
    DWORD consoleSize = csbi.dwSize.X;
    DWORD charsWritten;
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, startCoords, &charsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, startCoords, &charsWritten);
    setCursorPosition(0, lineNumber); // clearLine 후 커서를 해당 줄의 맨 앞으로 이동
}

// 생성자 정의
Player::Player(const std::string& name, int level, int hp, int stamina, int atk, int def)
    : Entity(name, level, hp, stamina, atk, def) 
{
    // 플레이어 정보 초기화
    this->EXP = 0;
    this->maxEXP = 100 * this->Level;
    this->Money = 0;
    this->posX = 0;
    this->posY = 0;
}

// 정보 반환 
int Player::GetMoney() const { return Money; }
int Player::GetEXP() const { return EXP; }
int Player::GetMaxEXP() const { return maxEXP; }
int Player::GetPosX() const { return posX; }
int Player::GetPosY() const { return posY; }

// 플레이어 좌표 이동 
void Player::Move(Direction dir) 
{
    int nextX = posX;
    int nextY = posY;

    switch (dir) 
    {
    case Direction::UP:    nextY--; break;
    case Direction::DOWN:  nextY++; break;  
    case Direction::LEFT:  nextX--; break;
    case Direction::RIGHT: nextX++; break;
    }

    // 좌표 유효성 검사
    if (nextX >= 0 && nextY >= 0) 
    {
        posX = nextX;
        posY = nextY;
    }
    else 
    {
        std::cout << "***** 그 방향으로 이동할 수 없습니다. (좌표 음수 진입) *****" << std::endl;
    }
}

// 좌표 출력 (테스트용)
void Player::PrintPosition() const 
{
    std::cout << "현재 위치: (" << posX << ", " << posY << ")" << std::endl;
}

void Player::PrintStatus() const
{
    std::cout << "***** 플레이어 상태 출력 ******" << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 이름(Name) : " << GetName() << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 레벨(LV) : " << GetLv() << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 공격력(ATK) : " << GetStamina() << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ (현재 EXP: " << GetEXP() << "/" << GetMaxEXP() << ")" << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 스테미너(Stamina) : " << GetStamina() << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 공격력(ATK) : " << GetATK() << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 방어력(DEF) : " << GetDEF() << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "  ㄴ 현재 위치: (" << GetPosX() << ", " << GetPosY() << ")" << std::endl;
    std::cout << "********************************" << std::endl;
}

// 경험치 획득
void Player::AddEXP(int amount) 
{
    EXP += amount;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "***** " << Name << "이(가) 경험치 " << amount << "을(를) 획득했습니다. (현재 EXP: " << EXP << "/" << maxEXP << ") *****" << std::endl;
    
    // 경험치량 충족 시, 레벨 업
    while (EXP >= maxEXP) { LevelUP(); }
}

// 레벨 업 
void Player::LevelUP() 
{
    // 경험치 초기화 및 요구량 재설정
    EXP -= maxEXP;
    Level++;
    maxEXP = 100 * Level;

    // 레벨 업에 따른 스텟 상승
    HP += 20;
    Stamina += 10;
    ATK += 5;
    DEF += 2;

    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "***** 레벨업! " << Name << "의 레벨이 " << Level << "이(가) 되었습니다! *****" << std::endl;
    clearLine(getCurrentCursorLine());      // 커서 위치 가져오기 & 줄 초기화
    std::cout << "***** HP, 스태미나, 공격력, 방어력이 상승했습니다. *****" << std::endl;
}

// 스테미너 추가 (회복 또는 감소)
void Player::AddStamina(int amount)
{
    // 현재 스테미너에 amount 값을 더함 (amount가 음수면 감소)
    this->Stamina += amount;

    // 스테미너가 0 미만으로 내려가지 않도록 처리
    if (this->Stamina < 0)
    {
        this->Stamina = 0;
    }

    clearLine(getCurrentCursorLine());
    if (amount >= 0)
    {
        std::cout << "***** 스테미너를 " << amount << "만큼 회복했습니다. (현재: " << this->Stamina << ") *****" << std::endl;
    }
    else
    {
        std::cout << "***** 스테미너를 " << -amount << "만큼 소모했습니다. (현재: " << this->Stamina << ") *****" << std::endl;
    }
}

// 카드 추가 
void Player::AddCard(std::shared_ptr<Card> newCard)
{
    deck.push_back(newCard);
    // std::cout << "***** [ " << newCard->C_GetName() << " ] 카드를 덱에 추가했습니다. *****" << std::endl;
}

// 보유 카드 출력
void Player::ShowCards() const
{
    clearLine(getCurrentCursorLine());
    std::cout << "========== 보유 카드 목록 ==========" << std::endl;
    if (deck.empty())
    {
        std::cout << "  보유한 카드가 없습니다." << std::endl;
    }
    else
    {
        for (size_t i = 0; i < deck.size(); ++i)
        {
            clearLine(getCurrentCursorLine());
            std::cout << "  " << i + 1 << ". " << deck[i]->C_GetName() << " (Cost: " << deck[i]->C_GetCost() << ")" << std::endl;
        }
    }
    std::cout << "==================================" << std::endl;
}

// 카드 사용
void Player::UseCard(int index)
{
    // 유효한 인덱스인지 확인 (사용자 입력은 1부터 시작하므로 index - 1)
    if (index <= 0 || index > deck.size())
    {
        clearLine(getCurrentCursorLine());
        std::cout << "***** 잘못된 번호입니다. *****" << std::endl;
        return;
    }

    // 덱에서 사용할 카드 선택
    std::shared_ptr<Card> cardToUse = deck[index - 1];

    // 카드의 실제 타입을 확인하기 위해 dynamic_pointer_cast 사용
    // 1. 이동 카드인지 확인
    if (auto moveCard = std::dynamic_pointer_cast<C_Move>(cardToUse))
    {
        posX += moveCard->M_GetX() * moveCard->M_GetDistance();
        posY += moveCard->M_GetY() * moveCard->M_GetDistance();
        clearLine(getCurrentCursorLine());
        std::cout << "***** [ " << moveCard->C_GetName() << " ] 카드를 사용하여 이동했습니다! *****" << std::endl;
    }
    // 2. 공격 카드인지 확인
    else if (auto attackCard = std::dynamic_pointer_cast<C_Attack>(cardToUse))
    {
        clearLine(getCurrentCursorLine());
        std::cout << "***** [ " << attackCard->C_GetName() << " ] 카드를 사용하여 공격력 " << attackCard->A_GetATK() << "으로 공격합니다! (현재는 효과 없음) *****" << std::endl;
    }
    // 3. 방어 카드인지 확인
    else if (auto guardCard = std::dynamic_pointer_cast<C_Guard>(cardToUse))
    {
        DEF += guardCard->G_GetDEF();
        clearLine(getCurrentCursorLine());
        std::cout << "***** [ " << guardCard->C_GetName() << " ] 카드를 사용하여 방어력이 " << guardCard->G_GetDEF() << "만큼 증가했습니다! *****" << std::endl;
    }

    // 사용한 카드를 덱에서 제거
    deck.erase(deck.begin() + (index - 1));
}

// 정보 설정 (Setter) 
void Player::SetMoney(int money)
{
    this->Money = money;
}

void Player::SetEXP(int exp)
{
    this->EXP = exp;
}

void Player::SetPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
}