#include "CheckPoint.h"

CheckPoint::CheckPoint(float x, float y)
	: m_rectangle(x, y, SIZE, SIZE, "res/shaders/basicRectangle.shader"), m_texture("res/textures/checkPoint.png"), m_color({ 2.0f, 0.0f, 2.0f, 1.0f })
{
	
}

bool CheckPoint::IsComplete(const Player& player) const
{
	if (CheckCollision(m_rectangle.m_transform, player.m_rectangle.m_transform))
		return true;

	return false;
}

void CheckPoint::Draw()
{
	m_texture.Bind();
	Renderer::DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader);
	m_texture.Unbind();
}