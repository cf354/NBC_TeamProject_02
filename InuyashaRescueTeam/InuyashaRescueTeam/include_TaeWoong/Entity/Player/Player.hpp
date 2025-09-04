#pragma once // ��� ���� �ߺ� ���� ����
#include "Entity.hpp" // �θ� Ŭ������ Entity ��� ����
#include <vector>
#include <memory> // std::shared_ptr ����� ���� �߰�
#include <conio.h> // ��Ʈ�ѷ� �Է��� ���� ���
#include <windows.h> // Windows API ���

// Ŭ���� ���� ���� (Card Ŭ���� ���� �� ��� �߰�)
class Card;

// ��ƿ��Ƽ �Լ�
void setCursorPosition(int x, int y);
void hideCursor();
int getCurrentCursorLine();
void clearLine(int lineNumber);

// ���� ������
enum class Direction 
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public Entity 
{
private:
    int Money;
    int EXP;
    int maxEXP;
    // ����Ʈ ������ shared_ptr ���
    std::vector<std::shared_ptr <Card>> deck;
    int posX;
    int posY;

    // ���� �� (��ü �ȿ����� ����)
    void LevelUP();

public:
    // ������ 
    Player(const std::string& name, int level, int hp, int stamina, int atk, int def);

    // ���� ��ȯ (Getter)
    int GetMoney() const;
    int GetEXP() const;
    int GetMaxEXP() const;
    int GetPosX() const;
    int GetPosY() const;

    // ���� ���� (Setter)
    void SetMoney(int money);
    void SetEXP(int exp);
    void SetPosition(int x, int y);

    // ��� �Լ� 
    void Move(Direction dir);
    void PrintPosition() const;
    void PrintStatus() const;
    void AddCard(std::shared_ptr<Card> newCard); // ī�� �߰�
    void AddEXP(int amount);
    void AddStamina(int amount);
    void ShowCards() const;     // ī�� ���
    void UseCard(int index);    // ī�� ���
};