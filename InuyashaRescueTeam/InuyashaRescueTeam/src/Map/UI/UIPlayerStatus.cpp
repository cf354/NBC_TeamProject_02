#include "Map/UI/UIPlayerStatus.h"
#include "Map/UI/UIBar.h"
#include "Map/UI/UIBox.h"
#include "GameManager/GameManager.h"

UIPlayerStatus::UIPlayerStatus()
{
    UIBox* uiBox = new UIBox();
    uiBox->SetParent(this);
    uiBox->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(0, 0));

    hpBar = new UIBar();
    hpBar->SetParent(this);
    hpBar->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(1, 1));
    hpBar->SetText(L"     HP = ");

    staminaBar = new UIBar();
    staminaBar->SetParent(hpBar);
    staminaBar->SetPosition(Anchor::LB, Vector2F(0.0f, 0.0f), Vector2D(0, 0));
    staminaBar->SetText(L"Stamina = ");
    staminaBar->SetColorBar(MColor::YELLOW);

    expBar = new UIBar();
    expBar->SetParent(staminaBar);
    expBar->SetPosition(Anchor::LB, Vector2F(0.0f, 0.0f), Vector2D(0, 0));
    expBar->SetText(L"    EXP = ");
    expBar->SetColorBar(MColor::CYAN);

    int boxSizeX = max(max(hpBar->GetSize().x, staminaBar->GetSize().x), expBar->GetSize().x) + 2;
    int boxSizeY = hpBar->GetSize().y + staminaBar->GetSize().y + expBar->GetSize().y + 2;
    uiBox->SetSize(boxSizeX, boxSizeY);
}

void UIPlayerStatus::Update()
{
    auto player = GAME_MANAGER->GetPlayer().lock();
    if (player != nullptr)
    {

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
