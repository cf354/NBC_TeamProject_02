#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>


enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    IGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

struct ConsoleCellData {
    WCHAR character;       // 콘솔 셀의 글자 (유니코드)
    int foregroundColor;   // 전경색 인덱스 (0-15)
    int backgroundColor;   // 배경색 인덱스 (0-15)

    // 생성자 (필요에 따라 오버로드 가능)
    // 기본 생성자: 초기값을 지정하지 않을 경우 사용됩니다.
    ConsoleCellData() : character(L'\0'), foregroundColor(0), backgroundColor(0) {}

    // 값 초기화 생성자: 특정 값으로 객체를 생성할 때 사용됩니다.
    ConsoleCellData(WCHAR ch, int fg, int bg) : character(ch), foregroundColor(fg), backgroundColor(bg) {}
};

//using namespace std;

class Particle
{
public:
    Particle(int spawnx, int spawny, int deadTick, Color color) : _Color(color), deadTick(deadTick) {
        spawnX = spawnx > 3 ? spawnx : 3;
        spawnY = spawny > 3 ? spawny : 3;
    }

    bool isDead = true;

private:
    int spawnX;
    int spawnY;

    int deadTick = 5;

    int currentTick = 0;
    void SetTick(int tick) {
        currentTick = tick;
    }

    Color _Color;

    bool data[5][5][5]
        = {
            {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}},
            {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}},
            {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}},
            {{0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0}},
            {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}
    };

public:
    void Spawn();

    void TickActive(std::vector<std::vector<ConsoleCellData>> _Data);

    void Draw(std::vector<std::vector<ConsoleCellData>> _Data);

    void DrawCellData(std::vector<std::vector<ConsoleCellData>> data, int x, int y);

    void RemoveParticle(std::vector<std::vector<ConsoleCellData>> data);

private:
    void tbColor(unsigned short textColor, unsigned short backColor) {
        int color = textColor + backColor * 16;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void GoToXY(int x, int y) {
        COORD pos = { x,y }; //x, y 좌표 설정
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void printHalfBlock(int x, int y, unsigned short Color) {
        tbColor(BLACK, Color);
        std::cout << "▀";
    }

    void printBlock(int x, int y, unsigned short Color) {
        tbColor(Color, BLACK);
        std::cout << "▀";
    }

    void printGround(int x, int y, unsigned short Color) {
        tbColor(7, Color);
        std::cout << " ";
    }

    int getConsoleCharWidth(WCHAR ch) {
        if (ch >= 0xAC00 && ch <= 0xD7A3) {
            return 2;
        }
        if (ch >= 0x4E00 && ch <= 0x9FFF) {
            return 2;
        }
        if (ch >= 0xFF00 && ch <= 0xFFEF) { // Full-width ASCII and punctuation
            return 2;
        }
        return 1;
    }
};