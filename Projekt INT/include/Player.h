#pragma once

#include "GameObject.h"
#include "Grid.h"
#include "Camera.h"

class Player : public GameObject
{
public:
	Player(Rectangle& rectangle, Color color, const std::string& texturePath1, const std::string& texturePath2);

	void Update(const Grid& grid);
private:
	void Draw() override;
	void CheckCollisions(const Grid& grid);
	void Move();
	void Input();

	float m_speedX, m_speedY;

	bool isOnGround, canJump, direction;
	
	Texture m_Texture2;
};
