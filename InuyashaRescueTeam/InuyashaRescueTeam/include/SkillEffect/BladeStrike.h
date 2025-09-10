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
            //SpawnParticle(0, 0, 30, ParticleColor::P_WHITE);

            //SpawnParticle(0, 21, 30, ParticleColor::P_WHITE);
            //SpawnParticle(0, 20, 30, ParticleColor::P_RED);
            SpawnParticle(0, 19, 30, ParticleColor::P_YELLOW);
            //SpawnParticle(0, 18, 30, ParticleColor::P_GREEN);
            //SpawnParticle(0, 17, 30, ParticleColor::P_BLUE);

            //for (size_t i = 0; i < 42; i++)
            //{
            //    //SpawnParticle(0, 21 - i, 30, ParticleColor::P_WHITE);
            //}

            /*for (size_t i = 0; i < 42; i++)
            {
                SpawnParticle(0, 21 - i, 30, ParticleColor::P_WHITE);
            }*/

            /*for (size_t i = 0; i < 20; i++)
            *

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
            */
        }
    }
};

