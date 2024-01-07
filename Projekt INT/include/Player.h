#pragma once

#include "GameObject.h"
#include "Grid.h"

class Player : public GameObject
{
public:
	Player(Rectangle& rectangle, Color color, const std::string& texturePath);

	void Update(const Renderer& renderer, const Grid& grid);
private:
	void Draw(const Renderer& renderer) override;
	void CheckCollisions(const Grid& grid);
	void Move();
	void Input();

	float m_speedX, m_speedY;
};
