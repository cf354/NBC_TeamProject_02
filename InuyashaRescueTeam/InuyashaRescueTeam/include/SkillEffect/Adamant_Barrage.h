#pragma once
#include "BattleUI/ParticleSystem.h"
#include  <cstdlib>

class Adamant_Barrage :public ParticleSystem
{
public:
    Adamant_Barrage(int deadTick) : ParticleSystem(deadTick) {}

protected:
    virtual void Tick() override {
        if (_CurrentTick == 0)
        {
            for (size_t j = 0; j < 100; j++)
            {
                SpawnParticle(-50 + j, -1, 30, ParticleColor::P_YELLOW);
                SpawnParticle(-50 + j, 0, 30, ParticleColor::P_YELLOW);
            }
        }

        if (_CurrentTick == 10)
        {
            for (size_t i = 0; i < 25; i++)
            {
                SpawnParticle(-100 + rand() % 200, -21 + rand() % 42, rand() % 5, ParticleColor::P_CYAN);
            }
        }

        if (_CurrentTick == 20)
        {
            for (size_t i = 0; i < 25; i++)
            {
                SpawnParticle(-100 + rand() % 200, -21 + rand() % 42, rand() % 5, ParticleColor::P_CYAN);
            }
        }
    }
};