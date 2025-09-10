#include "BattleUI/ParticleSystem.h"

void ParticleSystem::Run()
{
    _CurrentTick = 0;

    for (Particle p : _Particles)
    {
        p.Spawn();
    }

    const double TARGET_FPS = 30.0;
    // 한 프레임에 할당된 시간 (밀리초)
    const double MS_PER_FRAME = 1000.0 / TARGET_FPS; // 약 33.333... 밀리초

    //TickStart
    int size = _Particles.size();
    while (_CurrentTick < _EndTick)
    {
        size = _Particles.size();
        auto start_frame_time = std::chrono::high_resolution_clock::now();
        for (size_t index = 0; index < size; index++)
        {
            if (_Particles[index].isDead)
            {
                //_Particles[index].RemoveParticle(_Data); 
                _Particles.erase(_Particles.begin() + index);
                size = _Particles.size();
                index--;
            }
            else {
                //_Particles[index].TickActive(_Data);
                _Particles[index].TickActive();
            }
        }

        Tick();

        auto end_frame_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_frame_time = end_frame_time - start_frame_time;

        // 한 프레임 작업에 걸린 시간을 제외하고 남은 시간을 hybridDelay로 대기
        double remaining_time_ms = MS_PER_FRAME - elapsed_frame_time.count();

        _CurrentTick++;
        if (remaining_time_ms > 0) {
            hybridDelay(remaining_time_ms);
        }
    }

    for (Particle p : _Particles)
    {
        p.isDead = true;
        p.RemoveParticle(_Data);
    }

    int color = 7 + 0 * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ParticleSystem::Active(int activeX, int activeY)
{
    _ActiveX = activeX + _CanvasX;
    _ActiveY = activeY + _CanvasY;

    Run();
}

void ParticleSystem::Tick()
{
    /*
    if (_CurrentTick == 0)
    {
        for (size_t i = 0; i < 20; i++)
        {
            SpawnParticle(-10 + i, 10 - i, 30, RED);
        }

        for (size_t i = 0; i < 20; i++)
        {
            SpawnParticle(-10 + i, 10 - i + 5, 50, RED);
        }

        for (size_t i = 0; i < 20; i++)
        {
            SpawnParticle(-10 + i, 10 - i + 10, 70, RED);
        }
    }
    */
}

void ParticleSystem::SpawnParticle(int x, int y, int deadTick, ParticleColor color)
{
    int p_spawnx = _ActiveX + x;
    int p_spawny = _ActiveY + y;
    if (p_spawnx - 3 < _CanvasX || p_spawnx + 3 > _CanvasX + _CanvasWidth) return;
    if (p_spawny - 3 < _CanvasY || p_spawny + 3 > _CanvasY + _CanvasHeight) return;

    ConsoleCellData backGroundData[3][5];

    for (size_t Y = 0; Y < 3; Y++)
    {
        for (size_t X = 0; X < 5; X++)
        {
            int _Y = p_spawny - _CanvasY + Y;
            int _X = p_spawnx + _CanvasX + X;

            backGroundData[Y][X].backgroundColor = _Data[_Y][_X].backgroundColor;
            backGroundData[Y][X].character = _Data[_Y][_X].character;
            backGroundData[Y][X].foregroundColor = _Data[_Y][_X].foregroundColor;
        }
    }

    Particle newParticle(p_spawnx, p_spawny, deadTick, color, backGroundData);
    newParticle.Spawn();
    _Particles.push_back(newParticle);
}

void ParticleSystem::preciseDelay(double microseconds)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER startCounter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startCounter);
    double targetCounterValue = startCounter.QuadPart + (microseconds * frequency.QuadPart / 1000000.0);
    LARGE_INTEGER currentCounter;
    do {
        QueryPerformanceCounter(&currentCounter);
    } while (currentCounter.QuadPart < targetCounterValue);
}

void ParticleSystem::hybridDelay(double milliseconds)
{
    double microseconds = milliseconds * 1000.0; // 요청된 밀리초를 마이크로초로 변환

    // 대략적인 최소 슬립 가능한 시간 (ms)
    // 윈도우 기본 틱은 보통 10~15ms, timeBeginPeriod(1) 시 1ms
    // 여기서는 넉넉하게 5ms 정도를 '정확하게' 재는 부분으로 둠
    const double preciseThreshold_us = 5000.0; // 5 밀리초

    if (microseconds <= preciseThreshold_us) {
        // 짧은 시간은 바로 정밀 지연 사용
        preciseDelay(microseconds);
    }
    else {
        // 긴 시간은 Sleep으로 대부분 대기
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(microseconds - preciseThreshold_us)));
        // 그리고 남은 시간은 정밀 지연 사용
        preciseDelay(preciseThreshold_us);
    }
}

ConsoleCellData ParticleSystem :: getConsoleCharInfoAt(int x, int y) {
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