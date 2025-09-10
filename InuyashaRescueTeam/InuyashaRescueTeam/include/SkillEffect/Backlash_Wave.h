#pragma once
#include "BattleUI/ParticleSystem.h"

class Backlash_Wave :public ParticleSystem
{
public:
    Backlash_Wave(int deadTick) : ParticleSystem(deadTick) {}

protected:
    virtual void Tick() override {
        if (_CurrentTick == 0 )
        {
            for (size_t i = 0; i < 42; i++)
            {
                SpawnParticle(25, 21 - i, 3, ParticleColor::P_CYAN);
                SpawnParticle(27, 21 - i, 3, ParticleColor::P_CYAN);
                SpawnParticle(29, 21 - i, 3, ParticleColor::P_CYAN);
            }
        }

        if (_CurrentTick == 5)
        {
            for (size_t i = 0; i < 42; i++)
            {
                SpawnParticle(31, -21 + i, 3, ParticleColor::P_YELLOW);
                SpawnParticle(33, -21 + i, 3, ParticleColor::P_YELLOW);
                SpawnParticle(35, -21 + i, 3, ParticleColor::P_YELLOW);
            }
        }

        if (_CurrentTick == 10)
        {
            for (size_t i = 0; i < 42; i++)
            {
                SpawnParticle(37, 21 - i, 3, ParticleColor::P_CYAN);
                SpawnParticle(39, 21 - i, 3, ParticleColor::P_CYAN);
                SpawnParticle(41, 21 - i, 3, ParticleColor::P_CYAN);
            }                     
        }

        if (_CurrentTick == 15)
        {
            for (size_t i = 0; i < 42; i++)
            {
                SpawnParticle(43, -21 + i, 3, ParticleColor::P_YELLOW);
                SpawnParticle(45, -21 + i, 3, ParticleColor::P_YELLOW);
                SpawnParticle(47, -21 + i, 3, ParticleColor::P_YELLOW);
            }
        }

        if (_CurrentTick == 20)
        {
            for (size_t j = 48; j < 58; j++)
            {
                for (size_t i = 0; i < 42; i++)
                {
                    SpawnParticle(j, -21 + i, 3, ParticleColor::P_CYAN);
                }
            }
        }
    }
};

