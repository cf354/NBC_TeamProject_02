#pragma once
#include "BattleUI/ParticleSystem.h"

class BladesOfBlood :public ParticleSystem
{
public:
    BladesOfBlood(int deadTick) : ParticleSystem(deadTick) {}

protected:
    virtual void Tick() override {
        if (_CurrentTick == 0)
        {
            for (size_t j = 0; j < 50; j++)
            {
                for (size_t i = 0; i < 14; i += 4)
                {
                    SpawnParticle(j - 50, 7 - i, 3, ParticleColor::P_LIGHTRED);
                }
            }

            for (size_t j = 0; j < 50; j++)
            {
                for (size_t i = 0; i < 14; i += 4)
                {
                    SpawnParticle(j + 50, 7 - i, 3, ParticleColor::P_LIGHTRED);
                }
            }

            for (size_t j = 0; j < 50; j++)
            {
                for (size_t i = 0; i < 14; i += 4)
                {
                    SpawnParticle(j, 7 - i + 7, 3, ParticleColor::P_LIGHTRED);
                }
            }

            for (size_t j = 0; j < 50; j++)
            {
                for (size_t i = 0; i < 14; i += 4)
                {
                    SpawnParticle(j, 7 - i - 7, 3, ParticleColor::P_LIGHTRED);
                }
            }
        }
    }
};