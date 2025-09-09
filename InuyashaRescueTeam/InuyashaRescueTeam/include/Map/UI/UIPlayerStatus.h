#pragma once
#include "Map/UI/UI.h"

class UIBar;

class UIPlayerStatus : public UI
{
public:
    UIPlayerStatus();

    void Update() override;

private:
    UIBar* hpBar;
    UIBar* staminaBar;
    UIBar* expBar;
};

