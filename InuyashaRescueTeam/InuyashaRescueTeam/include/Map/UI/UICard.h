#pragma once
#include "Map/UI/UIBox.h"

class UIText;
class Card;

class UICard : public UIBox
{
public:
    UICard();
    virtual ~UICard();

    void Update() override;
    void Render() override;

    void SetData(Card* card);
    void ClearGrid();
    void UseGrid(int y, int x);
    void SetColorGrid(MColor color);

private:
    UIText* textName;
    vector<vector<char>> grid;
    int gridX, gridY;
    MColor colorGrid;
};

