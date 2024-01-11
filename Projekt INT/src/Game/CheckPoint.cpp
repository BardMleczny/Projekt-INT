#include "Game/CheckPoint.h"

CheckPoint::CheckPoint(float x, float y)
	: m_rectangle(x, y, SIZE, SIZE, "res/shaders/basicRectangle.shader"), m_texture("res/textures/checkPoint.png"), m_color({ 2.0f, 0.0f, 2.0f, 1.0f })
{
	
}

bool CheckPoint::IsComplete(const Player& player)
{
	if (CheckCollision(m_rectangle.m_transform, player.m_rectangle.m_transform))
		return true;

	return false;
}

void CheckPoint::Draw(const Renderer& renderer, Camera camera)
{
	m_texture.Bind();
	renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader, camera.GetMatrix());
	m_texture.Unbind();
}