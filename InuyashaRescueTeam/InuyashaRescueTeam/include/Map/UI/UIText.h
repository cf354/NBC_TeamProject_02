#pragma once
#include "UI.h"

using namespace std;

class UIText : public UI
{
public:
    void Render() override;

    void SetText(wstring text);
    void SetColor(MColor color);

    wstring GetText();

private:
    wstring text;
    MColor color = MColor::WHITE;
};

