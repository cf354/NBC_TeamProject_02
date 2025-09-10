#pragma once
#include "BattleUI/ParticleSystem.h"
#include  <cstdlib>

class IronReaver :public ParticleSystem
{
public:
    IronReaver(int deadTick) : ParticleSystem(deadTick) {}

protected:
    virtual void Tick() override {
        for (size_t i = 0; i < 3; i++)
        {
            SpawnParticle(-25 + rand() % 125, -7 + rand() % 36, 3, ParticleColor::P_YELLOW);
        }
    }
};

