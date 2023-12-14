#pragma once

#include "Renderer.h"

class Rectangle
{
public:
	float m_x, m_y;

	Rectangle(float x, float y, float width, float height);
	
	inline float GetWidth() const { return m_width; }
	inline float GetHeight()  const { return m_height; }

	
	IndexBuffer m_ib;
	VertexArray m_va;
private:
	float m_width, m_height;
	VertexBuffer m_vb;
	VertexBufferLayout m_layout;
};
