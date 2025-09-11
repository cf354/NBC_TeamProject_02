#pragma once

#include "Particle.h"
#include <thread> 
#include <chrono>

class ParticleSystem
{
public:
    ParticleSystem(int canvaswidth, int canvasheight, int canvasx, int canvasy, int activeX, int activeY, int endTick) {
        _CanvasWidth = 200;
        _CanvasHeight = 42;
        _CanvasX = 0;
        _CanvasY = 2;
        _EndTick = endTick;
        _ActiveX = activeX;
        _ActiveY = activeY;
        setupConsoleEncoding();
        SetData();
    }

    ParticleSystem(int endTick) {
        _CanvasWidth = 200;
        _CanvasHeight = 42;
        _CanvasX = 0;
        _CanvasY = 2;
        _EndTick = endTick;
        //_ActiveX = activeX;
        //_ActiveY = activeY;
        setupConsoleEncoding();
        SetData();
    }

protected:
    std::vector<Particle> _Particles;

    int _CanvasWidth;
    int _CanvasHeight;

    int _CanvasX;
    int _CanvasY;

    int _ActiveX;
    int _ActiveY;

    int _CurrentTick = 0;
    int _EndTick = 0;

    std::vector<std::vector<ConsoleCellData>> _Data;
public:
    void Run();
    void Active(int activeX, int activeY);

protected:
    virtual void Tick();

    void SpawnParticle(int x, int y, int deadTick, ParticleColor color);

    void SetData() {
        for (size_t y = 0; y < _CanvasHeight; y++)
        {
            _Data.push_back(std::vector<ConsoleCellData>());
            for (size_t x = 0; x < _CanvasWidth; x++)
            {
                _Data[y].push_back(getConsoleCharInfoAt(_CanvasX + x, _CanvasY + y));
            }
        }
    }

    void setupConsoleEncoding() {
        SetConsoleOutputCP(CP_UTF8);
        std::wcout.imbue(std::locale(""));
    }

    void preciseDelay(double microseconds);

    void hybridDelay(double milliseconds);

    ConsoleCellData getConsoleCharInfoAt(int x, int y);
};
