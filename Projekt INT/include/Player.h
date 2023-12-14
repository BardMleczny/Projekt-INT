#pragma once

#include "Rectangle.h"
#include "Renderer.h"
#include "Texture.h"

class Player{
public:
	void Draw(Renderer renderer);
	Rectangle rectangle;
private:
	void Move();
	Color color;
	//Texture texture;
	float speedX, speedY;
};
