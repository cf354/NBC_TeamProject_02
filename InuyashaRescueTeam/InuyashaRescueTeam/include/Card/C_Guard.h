#pragma once
#include "Card.h"
class C_Guard :public Card {
private:
    int DEF = 0;
public:
    C_Guard(std::string n, int C, int G, int D) :Card(n, C, G), DEF(D) {}
    int G_GetDEF() {
        return DEF;
    }
    virtual ~C_Guard() {}
};

