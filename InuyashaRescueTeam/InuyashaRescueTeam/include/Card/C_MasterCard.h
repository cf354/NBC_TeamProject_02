#pragma once
#include "Card.h"
class MasterCard :
    public Card
{
public:
    MasterCard(std::string n,int C,int G):Card(n,C,G) {};
};

