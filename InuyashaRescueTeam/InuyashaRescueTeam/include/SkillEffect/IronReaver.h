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
            SpawnParticle(-100 + rand() % 200, -21 + rand() % 42, rand() % 5, ParticleColor::P_YELLOW);
            SpawnParticle(-100 + rand() % 200, -21 + rand() % 42, rand() % 5, ParticleColor::P_BROWN);
        }
    }
};

