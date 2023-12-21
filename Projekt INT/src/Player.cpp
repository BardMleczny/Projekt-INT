#include "Player.h"

#include "Input.h"

Player::Player(Rectangle& rectangle, Color color, const std::string& texturePath)
	: m_rectangle(rectangle), m_color(color), m_speedX(0), m_speedY(0), m_texture(texturePath)
{

}

void Player::Draw(const Renderer& renderer)
{
	m_texture.Bind();
	renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader);
	m_texture.Unbind();
	Move();
}

void Player::Move()
{
	m_speedX = 0;
	m_speedY = 0;

	if (Input::isKeyDown(GLFW_KEY_A)){
		m_speedX += -3.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_D)) {
		m_speedX += 3.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_S)) {
		m_speedY += -3.0f;
	}
	if (Input::isKeyDown(GLFW_KEY_W)) {
		m_speedY += 3.0f;
	}
	m_rectangle.m_x += m_speedX;
	m_rectangle.m_y += m_speedY;
}
