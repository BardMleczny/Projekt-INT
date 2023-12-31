#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include <vector>

class NumberText
{
public:
	NumberText(int number, int size);
	~NumberText();
	int number;
	void Draw(float x, float y, const Renderer& renderer);
	Rectangle basicRectangle;
	Texture** numberTextures;
};
