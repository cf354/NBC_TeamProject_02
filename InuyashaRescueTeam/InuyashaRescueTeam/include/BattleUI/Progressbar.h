#pragma once
#include "UIWidget.h"
#include <string>

class Progressbar :public UIWidget
{
public:
	Progressbar(int width, float MaxValue, Color background, Color font, bool opposite) : UIWidget(width, 1) {
		_width = width < 9 ? 10 : width;
		_MaxValue = MaxValue >= 0 ? MaxValue : 0;
		_Color_Background = background;
		_Color_Font = font;
		_opposite = opposite;
	}

	Progressbar(int width, int x, int y, float MaxValue, Color background, Color font, bool opposite) : UIWidget(width, 1, x, y) {
		_width = width < 9 ? 10 : width;
		_MaxValue = MaxValue >= 0 ? MaxValue : 0;
		_Color_Background = background;
		_Color_Font = font;
		_opposite = opposite;
	}
protected:

private:
	bool _Is_ValueSet = false;

	float _Value = 0;
	float _MaxValue = 0;

	Color _Color_Background = Color::BLACK;
	Color _Color_Font = Color::WHITE;
	bool _opposite = false;
	const char* _Fillchar = "■";

public:
	virtual void Draw() override;
	void SetValue(int value) {
		_Value = _MaxValue > value ? value: _MaxValue;
		_Is_ValueSet = true;
	};

protected:

private:
	std::string ValueToString();
	std::string MaxValueToString();

};

