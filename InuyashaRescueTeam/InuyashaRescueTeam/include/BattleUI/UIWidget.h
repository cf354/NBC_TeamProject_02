#pragma once
#include <windows.h>
#include <iostream>

enum Color {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	IGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

class UIWidget
{
public:
	UIWidget(int width, int height) : _spawnX(0), _spawnY(0) {
		SetWidth(width);
		SetHeight(height);
	}

	UIWidget(int width, int height, int spawnX, int spawnY) {
		SetWidth(width);
		SetHeight(height);
		SetSpawnX(spawnX);
		SetSpawnY(spawnY);
	}

protected:
	int _width = 0;

	int _height = 0;

	int _spawnX = 0;

	int _spawnY = 0;

private:

public:
	virtual void Draw() = 0;

	void SetWidth(int width) {
		_width = width >= 0 ? width : 0;
	}

	void SetHeight(int height) {
		_height = height >= 0 ? height : 0;
	}

	void SetSpawnX(int X) {
		_spawnX = X >= 0 ? X : 0;
	}

	void SetSpawnY(int Y) {
		_spawnY = Y >= 0 ? Y : 0;
	}

	const int GetWidth() const {
		return _width;
	}

	const int Getheight() const {
		return _height;
	}

	const int GetX() const {
		return _spawnX;
	}

	const int GetY() const {
		return _spawnY;
	}

	const int GetLeft() const {
		return _spawnX;
	}

	const int GetRight() const {
		return _spawnX + _width;
	}

	const int GetTop() const {
		return _spawnY;
	}

	const int GetBottom() const {
		return _spawnY + _height;
	}

protected:
	void GoToXY(int x, int y);

	void tbColor(unsigned short textColor = 7, unsigned short backColor = 0);

private:

};