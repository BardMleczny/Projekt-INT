#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include <vector>

class NumberText
{
public:
	NumberText(int value, int fontSize);
	~NumberText();
	int value;
	void Draw(float x, float y, const Renderer& renderer);
	Rectangle basicRectangle;
	Texture** numberTextures;
};
