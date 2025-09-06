#pragma once // 헤더 파일 중복 포함 방지
#include "Entity\Entity.h" // 부모 클래스인 Entity 헤더 포함
#include <vector>
#include <memory> // std::shared_ptr 사용을 위해 추가
#include <conio.h> // 컨트롤러 입력을 위한 헤더
#include <windows.h> // Windows API 사용

// 클래스 전방 선언 (Card 클래스 구현 후 헤더 추가)
class Card;

// 유틸리티 함수
void setCursorPosition(int x, int y);
void hideCursor();
int getCurrentCursorLine();
void clearLine(int lineNumber);

// 방향 열거형
enum class Direction 
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    // 대각선
    UP_LEFT,    // 북서 
    UP_RIGHT,   // 북동 
    DOWN_LEFT,  // 남서 
    DOWN_RIGHT  // 남동 
};

class Player : public Entity 
{
private:
    int Money;
    int EXP;
    int maxEXP;
    // 스마트 포인터 shared_ptr 사용
    std::vector<std::shared_ptr <Card>> deck;
    // 현재 위치
    int posX;
    int posY;
    // 유효한 이전 위치
    int Prev_posX;
    int Prev_posY;

    // 레벨 업 (객체 안에서만 통제)
    void LevelUP();

public:
    // 생성자 
    Player(const std::string& name, int level, int hp, int stamina, int atk, int def);

    // 정보 반환 (Getter)
    int GetMoney() const;
    int GetEXP() const;
    int GetMaxEXP() const;
    int GetPosX() const;
    int GetPosY() const;
    std::vector<std::shared_ptr<Card>> GetDeck();

    // 정보 설정 (Setter)
    void SetMoney(int money);
    void SetEXP(int exp);
    void SetPosition(int x, int y);

    // 멤버 함수 
    void Move(Direction dir);
    void PrintPosition() const;
    void PrintStatus() const;
    void AddCard(std::shared_ptr<Card> newCard); // 카드 추가
    void AddEXP(int amount);
    // void AddStamina(int amount); // 스테미너 제한 이관 -> Entity 클래스
    void ShowCards() const;     // 카드 출력
    
};