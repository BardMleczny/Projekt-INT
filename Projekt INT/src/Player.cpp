#include "Player.h"

Player::Player(Rectangle& rectangle, Color color/*, Texture texture*/)
	: m_rectangle(rectangle), m_color(color), m_speedX(0), m_speedY(0)
{

}

void Player::Draw(const Renderer& renderer)
{
	renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader);
	Move();
}

void Player::Move()
{

}