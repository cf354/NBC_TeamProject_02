#include "Map/UI/UIInventory.h"
#include "GameManager/GameManager.h"
#include "Entity/Player.h"
#include "Map/UI/UICard.h"
#include "Map/UI/UIText.h"

UIInventory::UIInventory()
{
    SetSize(160, 44);

    UIText* textName = new UIText();
    textName->SetParent(this);
    textName->SetText(L" INVENTORY ");
    textName->SetSize(textName->GetText().size(), 1);
    textName->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(2, 0));

    int typeCount = 4;      // 자리 없음 (스크롤바 만들 시간 없음)
    uiCards = vector<vector<UICard*>>(typeCount);
    vector<wstring> wType = { L"[MOVE]", L"[ATTACK]", L"[MASTER]", L"[ETC]" };
    for (int i = 0; i < typeCount; i++)
    {
        UIText* textType = new UIText();
        textType->SetParent(this);
        textType->SetSize(16, 1);
        textType->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(2, i * 10 + 3));
        textType->SetText(wType[i]);
    }
    SetData();
}

UIInventory::~UIInventory()
{
    for (UICard* card : usingList)
    {
        delete card;
    }
    usingList.clear();
    
    for (UICard * card : unusingList)
    {
        delete card;
    }
    unusingList.clear();
}

void UIInventory::Render()
{
    if (!isActive)
        return;

    UIBox::Render();
}

void UIInventory::SetData()
{
    Reset();
    auto player = GAME_MANAGER->GetPlayer().lock();
    if (player != nullptr)
    {
        // 카드 너무 많아서 우측으로 튀어나오는 경우는 처리 안함
        const auto& deck = player->GetDeck();
        for (int i = 0; i < deck.size(); i++)
        {
            UICard* card = GetCard();
            auto data = deck[i].get();
            card->SetData(data);
            int idx = 0;
            if (C_Move* cMove = dynamic_cast<C_Move*>(data))
            {
                idx = 0;
                card->SetColorGrid(MColor::BLUE);
            }
            else if (C_Attack* cAtk = dynamic_cast<C_Attack*>(data))
            {
                idx = 1;
                card->SetColorGrid(MColor::RED);
            }
            else if (MasterCard* cMaster = dynamic_cast<MasterCard*>(data))
            {
                idx = 2;
                card->SetColorGrid(MColor::CYAN);
            }
            else
            {
                idx = 3;
                card->SetColorGrid(MColor::LIGHTGREEN);
            }
            card->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(uiCards[idx].size() * 10 + 2, idx * 10 + 4));
            uiCards[idx].push_back(card);
        }
    }
}

void UIInventory::Reset()
{
    for (int i = 0; i < uiCards.size(); i++)
    {
        uiCards[i].clear();
    }

    while (!usingList.empty())
    {
        ReturnCard(usingList.front());
    }
}

UICard* UIInventory::GetCard()
{
    UICard* card;
    if (unusingList.empty())
    {
        card = new UICard();
        card->SetParent(this);
    }
    else
    {
        card = unusingList.front();
        unusingList.pop_front();
    }
    card->SetActive(true);
    usingList.push_back(card);
    return card;
}

void UIInventory::ReturnCard(UICard* card)
{
    auto it = find(usingList.begin(), usingList.end(), card);
    if (it != usingList.end())
    {
        usingList.erase(it);
    }
    card->SetActive(false);
    unusingList.push_back(card);
}
