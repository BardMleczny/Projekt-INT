#pragma once

#include "GameObject.h"
#include "Rectangle.h"
#include "Player.h"

class CheckPoint
{
public:
	CheckPoint(float x, float y);

	void Draw(const Renderer& renderer, Camera camera);

	bool IsComplete(const Player& player);
private:
	const float SIZE = 64;

	Rectangle m_rectangle;
	Texture m_texture;
	Color m_color;
};
