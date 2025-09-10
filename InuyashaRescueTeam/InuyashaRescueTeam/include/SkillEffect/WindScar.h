#pragma once
#include "BattleUI/ParticleSystem.h"

class WindScar :public ParticleSystem
{
public:
    WindScar(int deadTick) : ParticleSystem(deadTick) {}

protected:
    virtual void Tick() override {
        if (_CurrentTick == 0)
        {
            for(int i = -50; i < 50; i++)
            {
                for (int j = 0; j < 14; j+=3)
                {
                    SpawnParticle(i, j, 3, ParticleColor::P_LIGHTBLUE);
                    SpawnParticle(i, j + 1, 3, ParticleColor::P_BLUE);
                    SpawnParticle(i, j + 2, 3, ParticleColor::P_CYAN);
                }
            }
        }
    }
};