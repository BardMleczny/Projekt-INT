#pragma once

#include "Rectangle.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject(Rectangle& rectangle, Color color, const std::string& texturePath);
	GameObject(Rectangle& rectangle, Color color, const Texture& texture);
	GameObject();
	virtual void Draw(const Renderer& renderer, Camera camera);
	Rectangle m_rectangle;
	Color m_color;
	Texture m_texture;
};