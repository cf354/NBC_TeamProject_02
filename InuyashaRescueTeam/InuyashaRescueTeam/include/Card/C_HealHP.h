#pragma once
#include "Card.h"
class C_HealHP :
    public Card
{

private:
    int Hamount = 0;
public:
    C_HealHP(std::string n, int C, int G,int h) :Card(n, C, G),Hamount(h) {
    }
    int GetHamount() { return Hamount; }
    virtual ~C_HealHP() {};
};

