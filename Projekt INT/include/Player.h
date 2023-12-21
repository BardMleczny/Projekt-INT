#pragma once

#include "Rectangle.h"
#include "Renderer.h"
#include "Texture.h"

class Player
{
public:
	Player(Rectangle& rectangle, Color color, const std::string& texturePath);

	void Draw(const Renderer& renderer);
	Rectangle m_rectangle;
private:
	void Move();
	Color m_color;
	Texture m_texture;
	float m_speedX, m_speedY;
};
