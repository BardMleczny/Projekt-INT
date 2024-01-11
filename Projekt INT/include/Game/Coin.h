#pragma once

#include "Engine/GameObject.h"
#include "Engine/Rectangle.h"
#include "Game/Player.h"

class Coin
{
public:
	Coin(float x, float y);
	Coin();
	
	void Draw(const Renderer& renderer, Camera camera);

	bool IsPicked(const Player& player);

	bool canBeDrawn = false;
private:
	const float SIZE = 40;

	Rectangle m_rectangle;
	Texture m_texture;
	Color m_color;
};
