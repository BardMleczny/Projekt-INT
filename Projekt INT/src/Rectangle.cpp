#include "Rectangle.h"

#include "VertexBufferLayout.h"

Rectangle::Rectangle(float x, float y, float width, float height)
	: m_x(x), m_y(y), m_width(width), m_height(height), m_va(), m_ib()
{
	float data[] = {
		0.0f,    0.0f,     0.0f, 0.0f,
		m_width, 0.0f,     1.0f, 0.0f,
		m_width, m_height, 1.0f, 1.0f,
		0.0f,    m_height, 0.0f, 1.0f
	};

	VertexBuffer vb(data, 16);

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_va.AddBuffer(vb, layout);
}