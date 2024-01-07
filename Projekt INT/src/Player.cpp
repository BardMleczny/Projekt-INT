#include "Player.h"

#include "Input.h"

#include <iostream>

Player::Player(Rectangle& rectangle, Color color, const std::string& texturePath)
	: GameObject::GameObject(rectangle, color, texturePath), m_speedX(0), m_speedY(0)
{

}	

void Player::Update(const Renderer& renderer, const Grid& grid)
{
	Draw(renderer);
	Input();
	CheckCollisions(grid);
	Move();
}

void Player::Draw(const Renderer& renderer)
{
	GameObject::Draw(renderer);
}

void Player::CheckCollisions(const Grid& grid)
{
	for (int i = 0; i < grid.size; i++)
	{
		if (grid.tiles[i].type != TerrainType::DEFAULT && grid.tiles[i].type != TerrainType::SKY)
		{
			if (grid.tiles[i].transform.y < m_rectangle.m_transform.y + m_rectangle.GetHeight() && CheckCollision(m_rectangle.m_transform, grid.tiles[i].transform))
			{
				m_speedY = 0;
			}
			if (grid.tiles[i].transform.y + grid.tiles[i].transform.height > m_rectangle.m_transform.y && CheckCollision(m_rectangle.m_transform, grid.tiles[i].transform))
			{
				m_speedY = 0;
			}
			if (grid.tiles[i].transform.x + grid.tiles[i].transform.width < m_rectangle.m_transform.x && CheckCollision(m_rectangle.m_transform, grid.tiles[i].transform))
			{
				m_speedX = 0;
			}
			if (grid.tiles[i].transform.x > m_rectangle.m_transform.x + m_rectangle.GetWidth() && CheckCollision(m_rectangle.m_transform, grid.tiles[i].transform))
			{
				m_speedX = 0;
			}
		}
	}
}

void Player::Move()
{
	m_rectangle.m_transform.x += m_speedX;
	m_rectangle.m_transform.y += m_speedY;
}

void Player::Input()
{
	m_speedX = 0;

	if (Input::isKeyDown(GLFW_KEY_A)) {
		m_speedX += -3.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_D)) {
		m_speedX += 3.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_W)) {
		m_speedY = 10.0f;
	}
	if(m_speedY > -10.0f)
	{
		m_speedY -= 2.5f;
	}
}