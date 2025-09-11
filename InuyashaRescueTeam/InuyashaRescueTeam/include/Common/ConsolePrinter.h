#pragma once
#include <Windows.h>
#include "Singleton.h"
#include "Map/MapTypes.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define DATA_WIDTH 208
#define DATA_HEIGHT 52

using namespace Map;

class ConsolePrinter : public Singleton<ConsolePrinter>
{
public:
	void Init();
	void Update();

	void SetConsole();

	void ScreenClear();
	void ScreenFlip();
	void ScreenPrint();
	void ScreenRelease();
	void Render();

    void SetConsoleFont(int idx);

    bool ScreenTransition_Swipe();
    void MakePattern_Swipe(int frame, int maxFrame, wchar_t(&outPattern)[DATA_HEIGHT][DATA_WIDTH]);

    void SetActiveBuffer(int hIdx);

	void DataClear();
	void SetData(int y, int x, wchar_t c, MColor textColor = MColor::WHITE, MColor BackColor = MColor::BLACK);

private:
	HANDLE hConsole[2];									// 깜빡임 없애기 위해 버퍼 2개 사용
	int hIdx = 0;       // 다음에 출력할 버퍼 인덱스

	wchar_t data[DATA_HEIGHT][DATA_WIDTH];			// 전체 데이터
    WORD attribute[DATA_HEIGHT][DATA_WIDTH];            // 글자 색
};

#define CONSOLE_PRINTER (ConsolePrinter::GetInstance())
