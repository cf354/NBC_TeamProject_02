#pragma once
#include "Map/UI/UIBox.h"

class UIText;
class UIBar;

class UIPlayerStatus : public UIBox
{
public:
    UIPlayerStatus();
    virtual ~UIPlayerStatus();

    void Update() override;

private:
    UIText* textLevel;
    UIBar* hpBar;
    UIBar* staminaBar;
    UIBar* expBar;
};

