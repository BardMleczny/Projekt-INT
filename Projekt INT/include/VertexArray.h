#pragma once
#include "../include/VertexBuffer.h"
//#include "../include/VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray 
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
private: 
	unsigned int m_RendererID;
};