#pragma once

#include "Rectangle.h"
#include "Player.h"

class Coin
{
public:
	Coin(float x, float y);
	Coin();
	
	void Draw();

	bool IsPicked(const Player& player);

	bool canBeDrawn = false;
private:
	const float SIZE = 40;

	Rectangle m_rectangle;
	Texture m_texture;
	Color m_color;
};
