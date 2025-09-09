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

using namespace std;

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

    void TickActive(vector<vector<ConsoleCellData>> _Data);

    void Draw(vector<vector<ConsoleCellData>> _Data);

    void DrawCellData(vector<vector<ConsoleCellData>> data, int x, int y);

    void RemoveParticle(vector<vector<ConsoleCellData>> data);

private:
    ConsoleCellData getConsoleCharInfoAt(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 출력 버퍼 핸들
        if (hConsole == INVALID_HANDLE_VALUE) {
            std::cerr << "오류: 콘솔 핸들을 가져올 수 없습니다." << std::endl;
            return { L'?', -1, -1 }; // 오류 값 반환
        }

        // ReadConsoleOutput 함수는 사각형 영역을 읽습니다.
        // 여기서는 1x1 크기의 사각형 영역(단일 셀)을 지정합니다.
        COORD bufferSize = { 1, 1 }; // 읽어올 버퍼의 크기 (1x1)
        COORD bufferCoord = { 0, 0 }; // 버퍼 내에서 읽기를 시작할 위치 (버퍼의 좌상단)

        CHAR_INFO charInfoBuffer[1]; // CHAR_INFO 구조체 하나를 저장할 배열

        // 읽어올 콘솔 화면 버퍼의 영역을 정의합니다.
        // 이 영역은 우리가 정보를 가져오려는 (x,y) 위치가 됩니다.
        SMALL_RECT readRegion;
        readRegion.Left = x;
        readRegion.Top = y;
        readRegion.Right = x; // 1x1 영역이므로 Left와 Right가 동일
        readRegion.Bottom = y; // 1x1 영역이므로 Top과 Bottom이 동일

        // ReadConsoleOutput 함수 호출:
        // 1. 콘솔 화면 버퍼 핸들
        // 2. 읽은 정보를 저장할 CHAR_INFO 버퍼의 주소
        // 3. CHAR_INFO 버퍼의 크기 (Width, Height)
        // 4. CHAR_INFO 버퍼 내에서 시작 위치 (보통 {0,0})
        // 5. 콘솔 화면 버퍼에서 읽어올 영역 (SMALL_RECT*)
        if (!ReadConsoleOutput(hConsole, charInfoBuffer, bufferSize, bufferCoord, &readRegion)) {
            //std::cerr << "오류: 콘솔 출력 정보를 읽는 데 실패했습니다. 오류 코드: " << GetLastError() << std::endl;
            return { L'?', -1, -1 }; // 오류 값 반환
        }

        // 읽어온 CHAR_INFO 구조체에서 정보 추출
        WCHAR character = charInfoBuffer[0].Char.UnicodeChar;
        WORD attributes = charInfoBuffer[0].Attributes;

        // 속성에서 전경색 (하위 4비트) 추출
        int foregroundColor = attributes & 0x0F;

        // 속성에서 배경색 (비트 4-7) 추출
        int backgroundColor = (attributes >> 4) & 0x0F;

        return { character, foregroundColor, backgroundColor };
    }

    void tbColor(unsigned short textColor, unsigned short backColor) {
        int color = textColor + backColor * 16;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void GoToXY(int x, int y) {
        COORD pos = { x,y }; //x, y 좌표 설정
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void printHalfBlock(int x, int y, unsigned short Color) {
        //GoToXY(x, y);
        tbColor(BLACK, Color);
        std::cout << "▀";
    }

    void printBlock(int x, int y, unsigned short Color) {
        //GoToXY(x, y);

        tbColor(Color, BLACK);
        std::cout << "▀";
    }

    void printGround(int x, int y, unsigned short Color) {
        //GoToXY(x, y);
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

    void setupConsoleEncoding() {
        // 1. 콘솔 출력 코드 페이지를 UTF-8로 설정
        // 이 코드는 main 함수 시작 부분에 딱 한 번만 호출하면 됩니다.
        SetConsoleOutputCP(CP_UTF8);

        // 2. std::wcout의 로케일 설정
        // imbue는 std::wcout 객체에 적용되며, 한 번 설정하면 해당 객체는 이 로케일을 계속 사용합니다.
        std::wcout.imbue(std::locale(""));
    }
};