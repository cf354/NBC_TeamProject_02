#pragma once
#include "UIWidget.h"
#include <string>

class Text : public UIWidget {
public:
	Text(std::string text, Color background, Color font) : UIWidget(text.size(), 1) {
		_Text = text;
		_Color_Background = background;
		_Color_Font = font;
	}

	Text(int x, int y, std::string text, Color background, Color font) : UIWidget(text.size(), 1, x, y) {
		_Text = text;
		_Color_Background = background;
		_Color_Font = font;
	}

	Text(int x, int y, int textsize, std::string text, Color background, Color font) : UIWidget(textsize, 1, x, y) {
		_Text = text;
		_Color_Background = background;
		_Color_Font = font;
	}

	virtual void Draw() override {
		GoToXY(_spawnX, _spawnY);
		tbColor(_Color_Font, _Color_Background);
		std::cout << _Text;
	}

protected:
	Color _Color_Background = Color::BLACK;
	Color _Color_Font = Color::WHITE;
private:
	std::string _Text;
};