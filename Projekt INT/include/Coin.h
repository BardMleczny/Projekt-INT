#pragma once

#include "GameObject.h"
#include "Rectangle.h"
#include "Player.h"

class Coin
{
public:
	Coin(float x, float y);
	Coin();
	
	void Draw(const Renderer& renderer, Camera camera);

	bool IsPicked(const Player& player);

	bool canBeDrawn = false;
private:
	float size = 32.0f;

	Rectangle m_rectangle;
	Texture m_texture;
	Color m_color;
};
