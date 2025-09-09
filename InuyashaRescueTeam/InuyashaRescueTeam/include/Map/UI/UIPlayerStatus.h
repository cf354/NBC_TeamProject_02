#pragma once
#include "Map/UI/UI.h"

class UIText;
class UIBar;

class UIPlayerStatus : public UI
{
public:
    UIPlayerStatus();

    void Update() override;

private:
    UIText* textLevel;
    UIBar* hpBar;
    UIBar* staminaBar;
    UIBar* expBar;
};

