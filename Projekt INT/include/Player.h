#pragma once

#include "GameObject.h"
#include "Grid.h"
#include "Camera.h"

class Player : public GameObject
{
public:
	Player(Rectangle& rectangle, Color color, const std::string& texturePath);

	void Update(const Renderer& renderer, const Grid& grid, Camera& camera);
private:
	void Draw(const Renderer& renderer, Camera camera) override;
	void CheckCollisions(const Grid& grid);
	void Move(Camera& camera);
	void Input();

	float m_speedX, m_speedY;

	bool isOnGround, canJump;
};
