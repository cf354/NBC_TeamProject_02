#pragma once
#include <string>
#include <Windows.h>
#include "UI.h"

using namespace std;

class Text : public UI
{
public:
	void Update() override;
	void Render() override;

	void SetText(wstring text, MColor color);

private:
	wstring text;
    MColor color;
};

