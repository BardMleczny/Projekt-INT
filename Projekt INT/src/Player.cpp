#include "Player.h"

#include "Input.h"

#include "Camera.h"

Player::Player(Rectangle& rectangle, Color color, const std::string& texturePath1, const std::string& texturePath2)
	: GameObject::GameObject(rectangle, color, texturePath1), m_speedX(0), m_speedY(0), m_Texture2(texturePath2)
{
	direction = true;
}	

void Player::Update(const Renderer& renderer, const Grid& grid, Camera& camera)
{
	Draw(renderer, camera);
	Input();
	CheckCollisions(grid);
	Move(camera);
}

void Player::Draw(const Renderer& renderer, Camera camera)
{
	if (m_speedX > 0)
	{
		GameObject::Draw(renderer, camera);
		direction = true;
	}
	else if (m_speedX < 0)
	{
		m_Texture2.Bind();
		renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader, camera.GetMatrix());
		m_Texture2.Unbind();
		direction = false;
	}
	else
	{
		if (direction)
		{
			GameObject::Draw(renderer, camera);
		}
		else
		{
			m_Texture2.Bind();
			renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader, camera.GetMatrix());
			m_Texture2.Unbind();
		}
	}
}

void Player::CheckCollisions(const Grid& grid)
{
	bool down = false, up = false, left = false, right = false;
	
	for (int i = 0; i < grid.size; i++)
	{
		TerrainType type = grid.tiles[i].type;
		if (type != TerrainType::DEFAULT && type != TerrainType::SKY && type != TerrainType::GRASS1 && type != TerrainType::GRASS2 &&
			type != TerrainType::GRASS3 && type != TerrainType::GRASS4 && type != TerrainType::GRASS5)
		{
			{
				Transform tempTransform = { m_rectangle.m_transform.x, m_rectangle.m_transform.y + m_speedY, m_rectangle.m_transform.width, m_rectangle.m_transform.height };

				if (grid.tiles[i].transform.y < tempTransform.y && CheckCollision(tempTransform, grid.tiles[i].transform))
				{
					if (m_speedY < 0)
					{
						m_speedY = 0;
					}
					down = true;
					isOnGround = true;
					canJump = true;
				}
				if (!(grid.tiles[i].transform.y < tempTransform.y + tempTransform.height && CheckCollision(tempTransform, grid.tiles[i].transform)))
				{
					isOnGround = false;
				}

				if (grid.tiles[i].transform.y + grid.tiles[i].transform.height > tempTransform.y && CheckCollision(tempTransform, grid.tiles[i].transform))
				{
					if (m_speedY > 0)
					{
						m_speedY = 0;
					}
				}
			}

			{
				Transform tempTransform = { m_rectangle.m_transform.x + m_speedX, m_rectangle.m_transform.y, m_rectangle.m_transform.width, m_rectangle.m_transform.height };

				if (grid.tiles[i].transform.x + grid.tiles[i].transform.width > tempTransform.x && CheckCollision(tempTransform, grid.tiles[i].transform))
				{
					if (m_speedX < 0)
					{
						m_speedX = 0;
						left = true;
					}
				}

				if (grid.tiles[i].transform.x < tempTransform.x + tempTransform.width && CheckCollision(tempTransform, grid.tiles[i].transform))
				{
					if (m_speedX > 0)
					{
						m_speedX = 0;
						right = true;
					}
				}
			}
		
			if (down)
				m_rectangle.m_transform.y = grid.tiles[i].transform.y + grid.tiles[i].transform.height; down = false;
			if (up)
				m_rectangle.m_transform.y = grid.tiles[i].transform.y + grid.tiles[i].transform.height; down = false;
			if (left)
				m_rectangle.m_transform.x = grid.tiles[i].transform.x + grid.tiles[i].transform.width; left = false;
			if(right)
				m_rectangle.m_transform.x = grid.tiles[i].transform.x - m_rectangle.m_transform.width; right = false;
		}
	}
}

void Player::Move(Camera& camera)
{
	m_rectangle.m_transform.x += m_speedX;
	m_rectangle.m_transform.y += m_speedY;

	camera.TransformMatrix(m_rectangle.m_transform.x, m_rectangle.m_transform.y);
	
}

void Player::Input()
{
	m_speedX = 0;

	if (Input::isKeyDown(GLFW_KEY_A)) {
		m_speedX -= 7.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_D)) {
		m_speedX += 7.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_W) && canJump) {
		m_speedY = 24.0f;
		isOnGround = false;
		canJump = false;
	}
	if (!isOnGround)
	{
		if (m_speedY > -12.0f)
		{
			m_speedY -= 0.8f;
		}
	}	
}