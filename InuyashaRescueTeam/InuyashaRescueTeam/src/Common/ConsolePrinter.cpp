#include "Common/ConsolePrinter.h"
#include <string>

using namespace std;

void ConsolePrinter::Init()
{
	SetConsole();
}

void ConsolePrinter::Update()
{
	DataClear();
}

void ConsolePrinter::SetConsole()
{
	system("title InuYasha-Rescue");

    hConsole[0] = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 마우스 커서 사이즈 조정 및 제거
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = FALSE;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole[0], &ConsoleCursor);
	SetConsoleCursorInfo(hConsole[1], &ConsoleCursor);

	HWND hwnd = GetConsoleWindow();
	HWND owner = GetWindow(hwnd, GW_OWNER);
	if (owner == nullptr)
	{
		// Windows10
		SetWindowPos(hwnd, nullptr, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		// Windows11
		SetWindowPos(owner, nullptr, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOMOVE | SWP_NOZORDER);
	}
}

void ConsolePrinter::ScreenClear()
{
	COORD coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hConsole[hIdx], ' ', DATA_WIDTH * DATA_HEIGHT, coor, &dw);
}

void ConsolePrinter::ScreenFlip()
{
	SetConsoleActiveScreenBuffer(hConsole[hIdx]);
	hIdx = 1 - hIdx;
}

void ConsolePrinter::ScreenPrint()
{
	DWORD dw;
	SetConsoleCursorPosition(hConsole[hIdx], { 0, 0 });
	//WriteFile(hConsole[hIdx], data, strlen(data), &dw, NULL);						// WriteFile로 한 문장으로 사용 시, 마지막에 마무리 문자(\0) 안 넣어주면 버그 발생
	for (short i = 0; i < DATA_HEIGHT; i++)
	{
		WriteConsoleOutputCharacter(hConsole[hIdx], data[i], DATA_WIDTH, { 0, i }, &dw);
	}
}

void ConsolePrinter::ScreenRelease()
{
	CloseHandle(hConsole[0]);
	CloseHandle(hConsole[1]);
}

/// <summary>
/// 콘솔 기존 내용 정리 후, data내용 콘솔에 출력
/// </summary>
void ConsolePrinter::Render()
{
	ScreenClear();
	ScreenPrint();
	ScreenFlip();
}

void ConsolePrinter::SetActiveBuffer(int hIdx)
{
    this->hIdx = hIdx;
    SetConsoleActiveScreenBuffer(hConsole[hIdx]);
}

/// <summary>
/// 출력할 데이터 Update에서 한 번 지워줌, 그 후 Render단계에서 Scene, UI로부터 데이터 입력받아서 출력
/// </summary>
void ConsolePrinter::DataClear()
{
	for (int i = 0; i < DATA_HEIGHT; i++)
	{
		for (int j = 0; j < DATA_WIDTH; j++)
		{
			data[i][j] = ' ';
		}
	}
}

void ConsolePrinter::SetData(int y, int x, wchar_t c)
{
	if (y < 0 || y >= DATA_HEIGHT || x < 0 || x >= DATA_WIDTH)
		return;

	data[y][x] = c;
}
