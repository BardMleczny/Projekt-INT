#pragma once

#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(Rectangle& rectangle, Color color, const std::string& texturePath);
	void Draw(const Renderer& renderer) override;
private:
	void Move();
	float m_speedX, m_speedY;
};
