#pragma once
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;      // 'BM' = 0x4D42
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
struct BMPInfoHeader {
    uint32_t biSize;          // 40
    int32_t  biWidth;
    int32_t  biHeight;        // <0 이면 top-down
    uint16_t biPlanes;        // 1
    uint16_t biBitCount;      // 24 또는 32
    uint32_t biCompression;   // 0 (BI_RGB)
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

#define LOGO      "../images/inu_logo.bmp"
#define KEY      "../images/inu_logo_key.bmp"
#define INU      "../images/inu.bmp"
#define KIKYO      "../images/kikyo.bmp"
#define KAGOME_GIF "../images/kagome_gif/frame_"

class ImagePrinter
{
public:
    void DrawImage(const char* filename, short OffsetX, short OffsetY);
    void printHalfBlock(unsigned int rt, unsigned int gt, unsigned int bt, unsigned int rb, unsigned int gb, unsigned int bb);
    void PlayGIF(const char* filename, int NumFrame, int delay, short OffsetX, short OffsetY);
};

