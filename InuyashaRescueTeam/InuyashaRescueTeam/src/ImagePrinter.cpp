#include "ImagePrinter.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>

void ImagePrinter::DrawImage(const char* filename, short OffsetX, short OffsetY)
{
    // ANSI(VT) escape 시퀀스 활성화
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode)) 
    {
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
       std::wcerr << L"파일 열기 실패\n";
       return;
    }

    BMPFileHeader fh; BMPInfoHeader ih;
    file.read(reinterpret_cast<char*>(&fh), sizeof(fh));
    file.read(reinterpret_cast<char*>(&ih), sizeof(ih));

    if (fh.bfType != 0x4D42)
    {
        std::wcerr << L"BMP 아님\n";
        return;
    }
    if (!(ih.biBitCount == 24 || ih.biBitCount == 32))
    {
        std::wcerr << L"24/32비트만 지원\n";
        return;
    }
    if (ih.biCompression != 0)
    { // BI_RGB만
        std::wcerr << L"압축 BMP 미지원\n";
        return;
    }

    const int width = ih.biWidth;
    const int heightAbs = ih.biHeight < 0 ? -ih.biHeight : ih.biHeight;
    const bool topDown = ih.biHeight < 0;

    const int bytesPerPixel = ih.biBitCount / 8;
    const int rowBytesRaw = width * bytesPerPixel;
    const int rowBytes = (ih.biBitCount == 24) ? ((rowBytesRaw + 3) & ~3) : rowBytesRaw;

    file.seekg(fh.bfOffBits, std::ios::beg);
    std::vector<uint8_t> buf(size_t(rowBytes) * heightAbs);
    file.read(reinterpret_cast<char*>(buf.data()), buf.size());
    if (!file)
    {
        std::wcerr << L"픽셀 읽기 실패\n";
        return;
    }
    for (int row = 0; row < heightAbs; row += 2) {
        // 한 문자는 세로 2픽셀을 표현 → yTop / yBot 계산
        int yTop = topDown ? row : (heightAbs - 1 - row);
        int yBot = topDown ? (row + 1) : (heightAbs - 1 - (row + 1));

        const uint8_t* lineTop = buf.data() + size_t(yTop) * rowBytes;
        const uint8_t* lineBot = (row + 1 < heightAbs) ? (buf.data() + size_t(yBot) * rowBytes) : nullptr;

        for (int x = 0; x < width; ++x) {
            const uint8_t* pT = lineTop + x * bytesPerPixel;
            unsigned int bT = pT[0], gT = pT[1], rT = pT[2]; // BMP는 BGR

            unsigned int rB = 0, gB = 0, bB = 0;
            if (lineBot) {
                const uint8_t* pB = lineBot + x * bytesPerPixel;
                bB = pB[0]; gB = pB[1]; rB = pB[2];
            }
            else {
                // 홀수 높이: 아래 픽셀이 없으면 검정(또는 rT,gT,bT 복제)으로 채움
                rB = gB = bB = 0;
            }

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast <short>(x + OffsetX), static_cast<short>(row/2 + OffsetY) });
            // "거의 검정" 처리(선택): 위/아래가 모두 아주 어두우면 공백 1칸
            if (rT < 8 && gT < 8 && bT < 8 && rB < 8 && gB < 8 && bB < 8) {
                std::wcout << L" ";
            }
            else {
                printHalfBlock(rT, gT, bT, rB, gB, bB);
            }
        }
    }
    std::wcout.flush();
}

void ImagePrinter::printHalfBlock(unsigned int rt, unsigned int gt, unsigned int bt, unsigned int rb, unsigned int gb, unsigned int bb)
{
    std::wstring msg = L"\x1b[38;2;" + std::to_wstring(rt) + L";" + std::to_wstring(gt) + L";" + std::to_wstring(bt) + L"m"
        L"\x1b[48;2;" + std::to_wstring(rb) + L";" + std::to_wstring(gb) + L";" + std::to_wstring(bb) + L"m"
        L"▀\x1b[0m";
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), msg.c_str(), (DWORD)msg.size(), nullptr, nullptr);
}
