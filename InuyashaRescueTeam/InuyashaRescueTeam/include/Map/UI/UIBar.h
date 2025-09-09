#pragma once
#include "Map/UI/UI.h"

class UIBar : public UI
{
public:
    UIBar();
    
    void Render() override;
    void SetValue(int currValue, int maxValue);
    void SetTextArea(int size);
    void SetText(wstring text);
    void SetColorBar(MColor color);

private:
    int maxValue;
    int currValue;
    int textSize = 20;
    wstring text;
    MColor colorBar;
};

