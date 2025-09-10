#pragma once
#include "BattleUI/ParticleSystem.h"

class BladeStrike :public ParticleSystem
{
public:
    BladeStrike(int deadTick) : ParticleSystem(deadTick) {}

protected:
    virtual void Tick() override {
        if (_CurrentTick == 0)
        {
            SpawnParticle(0, 0, 5, ParticleColor::P_WHITE);


            for (size_t i = 1; i < 21; i++)
            {
                SpawnParticle(0, i, 5, ParticleColor::P_WHITE);
            }

            for (size_t i = 1; i < 21; i++)
            {
                SpawnParticle(0, 0 - i, 5, ParticleColor::P_WHITE);
            }
        }
    }
};

