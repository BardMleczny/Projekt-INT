#include "Coin.h"

Coin::Coin(float x, float y)
	: m_rectangle(x, y, SIZE, SIZE, "res/shaders/basicRectangle_vertex.shader", "res/shaders/basicRectangle_fragment.shader"), m_texture("res/textures/coin.png"), canBeDrawn(true), m_color(Colors::WHITE)
{

}

Coin::Coin()
	: m_rectangle(0, 0, 0, 0, "res/shaders/basicRectangle_vertex.shader", "res/shaders/basicRectangle_fragment.shader"), m_texture("res/textures/tiles/empty.png"), canBeDrawn(false), m_color(Colors::WHITE)
{

}

bool Coin::IsPicked(const Player& player)
{
	if (CheckCollision(m_rectangle.m_transform, player.m_rectangle.m_transform))
		return true;

	return false;
}

void Coin::Draw()
{
	m_texture.Bind();
	Renderer::DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader);
	m_texture.Unbind();
}