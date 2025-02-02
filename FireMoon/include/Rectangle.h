#pragma once

#include "Renderer.h"

struct Transform 
{
	float x, y;
	float width, height;
};

class Rectangle
{
public:
	Transform m_transform;

	Rectangle(float x, float y, float width, float height, const std::string& shaderPath);
	
	void Bind();

	inline float GetWidth() const { return m_transform.width; }
	inline float GetHeight()  const { return m_transform.height; }

	
	IndexBuffer m_ib;
	VertexArray m_va;
	Shader m_shader;
private:
	VertexBuffer m_vb;
	VertexBufferLayout m_layout;
};

bool CheckCollision(Transform rectangle1, Transform rectangle2);