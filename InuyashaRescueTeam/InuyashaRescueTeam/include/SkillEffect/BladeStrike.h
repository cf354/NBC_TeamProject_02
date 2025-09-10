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
            for (size_t w = 0; w < 5; w++)
            {
                for (size_t i = 1; i < 21; i++)
                {
                    SpawnParticle(0 + w, i, 3, ParticleColor::P_YELLOW);
                }

                for (size_t i = 1; i < 21; i++)
                {
                    SpawnParticle(0 + w, 0 - i, 3, ParticleColor::P_YELLOW);
                }
                ///////////
                for (size_t i = 1; i < 21; i++)
                {
                    SpawnParticle(0 - w, i, 3, ParticleColor::P_YELLOW);
                }

                for (size_t i = 1; i < 21; i++)
                {
                    SpawnParticle(0 - w, 0 - i, 3, ParticleColor::P_YELLOW);
                }
            }
        }
    }
};

