#pragma once

#include "Engine/GameObject.h"
#include "Game/Grid.h"
#include "Engine/Camera.h"

class Player : public GameObject
{
public:
	Player(Rectangle& rectangle, Color color, const std::string& texturePath1, const std::string& texturePath2);

	void Update(const Renderer& renderer, const Grid& grid, Camera& camera);
private:
	void Draw(const Renderer& renderer, Camera camera) override;
	void CheckCollisions(const Grid& grid);
	void Move(Camera& camera);
	void Input();

	float m_speedX, m_speedY;

	bool isOnGround, canJump, direction;
	
	Texture m_Texture2;
};
