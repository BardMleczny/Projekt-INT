#include "Rectangle.h"

#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Rectangle::Rectangle(float x, float y, float width, float height, const std::string& shaderPath)
	: m_ib(new unsigned int[6] {0, 1, 2, 2, 3, 0}, 6), m_shader(shaderPath),
	m_vb(), m_layout(), m_va()
{
	m_transform = { x, y, width, height };
	float data[] = {
		0.0f,			   0.0f,			   0.0f, 0.0f,
		m_transform.width, 0.0f,			   1.0f, 0.0f,
		m_transform.width, m_transform.height, 1.0f, 1.0f,
		0.0f,			   m_transform.height, 0.0f, 1.0f
	};

	m_vb.LoadData(data, 16);

	m_layout.Push<float>(2);
	m_layout.Push<float>(2);

	m_va.AddBuffer(m_vb, m_layout);
	m_va.Unbind();
}

<<<<<<< Updated upstream
void Rectangle::Bind() 
{
	m_va.Bind();
	m_shader.Bind();
	m_ib.Bind();
	m_vb.Bind();
}
=======
//bool CheckCollision(Transform rectangle1, Transform rectangle2)
//{
//	if (
//		rectangle1.x < rectangle2.x + rectangle2.size &&
//		rectangle1.x + rectangle1.size > rectangle2.x &&
//		rectangle1.y < rectangle2.y + rectangle2.size &&
//		rectangle1.y + rectangle1.size > rectangle2.y
//		)
//}
>>>>>>> Stashed changes
