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

    for (int i = 0; i < 2; i++)
    {
        DWORD mode;
        GetConsoleMode(hConsole[i], &mode);
        SetConsoleMode(hConsole[i], mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

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
        // 버퍼, 윈도우 사이즈 조정
        SMALL_RECT rectTemp = { 0, 0, 1, 1 };
        SetConsoleWindowInfo(hConsole[0], TRUE, &rectTemp);
        SetConsoleWindowInfo(hConsole[1], TRUE, &rectTemp);

        COORD bufferSize = { DATA_WIDTH, DATA_HEIGHT };
        SetConsoleScreenBufferSize(hConsole[0], bufferSize);
        SetConsoleScreenBufferSize(hConsole[1], bufferSize);

        SMALL_RECT rectWindow = { 0, 0, DATA_WIDTH - 1, DATA_HEIGHT - 1};
        SetConsoleWindowInfo(hConsole[0], TRUE, &rectWindow);
        SetConsoleWindowInfo(hConsole[1], TRUE, &rectWindow);

        // 폰트 조정 (자연스러운 폰트)
        SetConsoleFont(0);
        SetConsoleFont(1);

        // 이거 아래 코드 Windows 10, 더블 버퍼링 환경에서 제대로 동작 안 함
		//SetWindowPos(hwnd, nullptr, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOMOVE | SWP_NOZORDER);
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
        WriteConsoleOutputCharacterW(hConsole[hIdx], data[i], DATA_WIDTH, { 0, i }, &dw);
        WriteConsoleOutputAttribute(hConsole[hIdx], attribute[i], DATA_WIDTH, { 0, i }, &dw);
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

void ConsolePrinter::SetConsoleFont(int idx)
{
    CONSOLE_FONT_INFOEX cfi = { 0 };
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole[idx], FALSE, &cfi);
    cfi.dwFontSize.X = 8;
    cfi.dwFontSize.Y = 16;
    wcscpy_s(cfi.FaceName, L"Cascadia Mono");
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsole[idx], FALSE, &cfi);
}

bool ConsolePrinter::ScreenTransition_Swipe()
{
    int maxFrame = 20;
    int delay = 25;
    for (int frame = 1; frame <= maxFrame; ++frame)
    {
        MakePattern_Swipe(frame, maxFrame, data);
        ScreenPrint();
        ScreenFlip();
        Sleep(delay);
    }
    return true;
}

void ConsolePrinter::MakePattern_Swipe(int frame, int maxFrame, wchar_t(&outPattern)[DATA_HEIGHT][DATA_WIDTH])
{
    /*wchar_t fillChar = L'.';
    double progress = double(frame) / maxFrame;*/

    //for (int y = 0; y < DATA_HEIGHT; ++y)
    //{
    //    for (int x = 0; x < DATA_WIDTH * progress; ++x)
    //    {
    //        outPattern[y][x] = fillChar;
    //    }
    //}

    //wchar_t fillChar = L'.';
    //for (int y = 0; y < DATA_HEIGHT; ++y)
    //{
    //    if ((y % maxFrame) + 1 == frame)
    //    {
    //        for (int x = 0; x < DATA_WIDTH; ++x)
    //        {
    //            outPattern[y][x] = fillChar;
    //        }
    //    }
    //}

    wchar_t fillChar = L'.';
    for (int y = 0; y < DATA_HEIGHT; ++y)
    {
        for (int x = 0; x < DATA_WIDTH; ++x)
        {
            if ((x % maxFrame) + 1 == frame)
            {
                outPattern[y][x] = fillChar;
            }
        }
    }
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
            attribute[i][j] = 0;
		}
	}
}

void ConsolePrinter::SetData(int y, int x, wchar_t c, MColor textColor, MColor BackColor)
{
	if (y < 0 || y >= DATA_HEIGHT || x < 0 || x >= DATA_WIDTH)
		return;

	data[y][x] = c;
    this->attribute[y][x] = (short)textColor + (short)BackColor * 16;
}
