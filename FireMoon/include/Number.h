#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include <vector>

class NumberText
{
public:
	NumberText(int value, int fontSize, Color color);
	~NumberText();
	int value;
	Color color;
	void Draw(float x, float y);
private:
	Rectangle basicRectangle;
	Texture** numberTextures;
};
