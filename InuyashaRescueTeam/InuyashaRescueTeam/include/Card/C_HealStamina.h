#pragma once
#include "Card.h"
class C_HealStamina :
    public Card
{

private:
    int Samount = 0;
public:
    C_HealStamina(std::string n, int C, int G, int h) :Card(n, C, G), Samount(h) {
    }
    int GetHamount() { return Samount; }
    virtual ~C_HealStamina() {};
};

