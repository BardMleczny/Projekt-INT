#include "Coin.h"

Coin::Coin(float x, float y)
	: m_rectangle(x, y, SIZE, SIZE, "res/shaders/basicRectangle.shader"), m_texture("res/textures/coin.png"), canBeDrawn(true), m_color({ 1.0f, 1.0f, 1.0f, 1.0f })
{

}

Coin::Coin()
	: m_rectangle(0, 0, 0, 0, "res/shaders/basicRectangle.shader"), m_texture("res/textures/tiles/empty.png"), canBeDrawn(false), m_color({ 1.0f, 1.0f, 1.0f, 1.0f })
{

}

bool Coin::IsPicked(const Player& player)
{
	if (CheckCollision(m_rectangle.m_transform, player.m_rectangle.m_transform))
		return true;

	return false;
}

void Coin::Draw(const Renderer& renderer, Camera camera)
{
	m_texture.Bind();
	renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader, camera.GetMatrix());
	m_texture.Unbind();
}