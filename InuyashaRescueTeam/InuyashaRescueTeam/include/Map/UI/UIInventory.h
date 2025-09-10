#pragma once
#include "Map/UI/UIBox.h"
#include <list>

class UICard;

class UIInventory : public UIBox
{
public:
    UIInventory();
    virtual ~UIInventory();

    void Render() override;

    void SetData();
    void Reset();
    UICard* GetCard();
    void ReturnCard(UICard* card);

private:
    vector<vector<UICard*>> uiCards;

    // 오브젝트 풀
    list<UICard*> usingList;
    list<UICard*> unusingList;
};

