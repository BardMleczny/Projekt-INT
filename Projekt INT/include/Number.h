#pragma once

#include "Rectangle.h"
#include "Texture.h"
#include <vector>

class NumberText
{
public:
	NumberText(int number, int size);
	~NumberText();

	void Draw(float x, float y, const Renderer& renderer);

	int number;
	Rectangle basicRectangle;
	Texture** numberTextures;
};
