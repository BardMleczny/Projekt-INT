#include "Rectangle.h"

#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Rectangle::Rectangle(float x, float y, float width, float height, const std::string& vertexFilepath, const std::string& fragmentFilepath)
	: m_shader(vertexFilepath, fragmentFilepath),
	m_vb(), m_layout(), m_va()
{
	m_transform = { x, y, width, height };
	float data[] = {
		0.0f,			   0.0f,			   0.0f, 0.0f,
		m_transform.width, 0.0f,			   1.0f, 0.0f,
		m_transform.width, m_transform.height, 1.0f, 1.0f,
		0.0f,			   m_transform.height, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_ib.LoadData(indices, 6);

	m_vb.LoadData(data, 16);

	m_layout.Push<float>(2);
	m_layout.Push<float>(2);

	m_va.AddBuffer(m_vb, m_layout);

	m_va.Unbind();
}

void Rectangle::Bind() 
{
	m_va.Bind();
	m_shader.Bind();
	m_ib.Bind();
	m_vb.Bind();
}

bool CheckCollision(Transform rectangle1, Transform rectangle2)
{
	return (
		rectangle1.x < rectangle2.x + rectangle2.width &&
		rectangle1.x + rectangle1.width > rectangle2.x &&
		rectangle1.y < rectangle2.y + rectangle2.height &&
		rectangle1.y + rectangle1.height > rectangle2.y
	);
}