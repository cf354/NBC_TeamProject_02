#include "Map/UI/UIPlayerStatus.h"
#include "Map/UI/UIBar.h"
#include "Map/UI/UIBox.h"
#include "Map/UI/UIText.h"
#include "GameManager/GameManager.h"

UIPlayerStatus::UIPlayerStatus()
{
    textLevel = new UIText();
    textLevel->SetParent(this);
    textLevel->SetSize(Vector2D(60, 1));
    textLevel->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(1, 1));

    hpBar = new UIBar();
    hpBar->SetParent(textLevel);
    hpBar->SetPosition(Anchor::LB, Vector2F(0.0f, 0.0f), Vector2D(0, 0));
    hpBar->SetText(L"HP      = ");

    staminaBar = new UIBar();
    staminaBar->SetParent(hpBar);
    staminaBar->SetPosition(Anchor::LB, Vector2F(0.0f, 0.0f), Vector2D(0, 0));
    staminaBar->SetText(L"Stamina = ");
    staminaBar->SetColorBar(MColor::YELLOW);

    expBar = new UIBar();
    expBar->SetParent(staminaBar);
    expBar->SetPosition(Anchor::LB, Vector2F(0.0f, 0.0f), Vector2D(0, 0));
    expBar->SetText(L"EXP     = ");
    expBar->SetColorBar(MColor::CYAN);

    int boxSizeX = 0, boxSizeY = 0;
    vector<UI*> allChildren = GetAllChildren();
    for (int i = 0; i < allChildren.size(); i++)
    {
        boxSizeX = max(boxSizeX, allChildren[i]->GetSize().x);
        boxSizeY += allChildren[i]->GetSize().y;
    }

    UIBox* uiBox = new UIBox();
    uiBox->SetParent(this);
    uiBox->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(0, 0));
    uiBox->SetSize(boxSizeX + 2, boxSizeY + 2);
}

void UIPlayerStatus::Update()
{
    auto player = GAME_MANAGER->GetPlayer().lock();
    if (player != nullptr)
    {
        if (textLevel != nullptr)
        {
            wstring strLevel = L" Lv. " + to_wstring(player->GetLv());
            textLevel->SetText(strLevel);
        }

        if (hpBar != nullptr)
        {
            hpBar->SetValue(player->GetHP(), player->GetMAXHP());
        }

        if (staminaBar != nullptr)
        {
            staminaBar->SetValue(player->GetStamina(), player->GetMAXStamina());
        }

        if (expBar != nullptr)
        {
            expBar->SetValue(player->GetEXP(), player->GetMaxEXP());
        }
    }

    UI::Update();
}
