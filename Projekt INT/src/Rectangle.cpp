#include "Rectangle.h"

#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Rectangle::Rectangle(float x, float y, float width, float height)
	: m_x(x), m_y(y), m_width(width), m_height(height), m_va(),
	m_ib(new unsigned int[6] {0, 1, 2, 2, 3, 0}, 6),
	m_vb(),
	m_layout()
{
	float data[] = {
		0.0f,    0.0f,     0.0f, 0.0f,
		m_width, 0.0f,     1.0f, 0.0f,
		m_width, m_height, 1.0f, 1.0f,
		0.0f,    m_height, 0.0f, 1.0f
	};

	m_vb.LoadData(data, 16);

	m_layout.Push<float>(2);
	m_layout.Push<float>(2);

	m_va.AddBuffer(m_vb, m_layout);
}
