#pragma once
#include "Card.h"
class C_Attack :
    public Card
{

    private:
        int ATK = 0;
        bool Range[3][3];
    public:
        C_Attack(std::string n, int C, int G, int A, bool r[3][3]) :Card(n, C, G), ATK(A) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Range[i][j] = r[i][j];
                }
            }
        }

        int A_GetATK() {
            return ATK;
        }
        bool (*A_GetRange())[3] {
            return Range;
        }
        virtual ~C_Attack() {}
};

