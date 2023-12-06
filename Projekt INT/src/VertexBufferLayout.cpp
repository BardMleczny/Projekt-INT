#include "VertexBufferLayout.h"

unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT:			return 4;
	case GL_UNSIGNED_INT:	return 4;
	case GL_UNSIGNED_BYTE:  return 1;
	}
	ASSERT(false);
	return 0;
}

VertexBufferLayout::VertexBufferLayout()
	: m_Stride(0) {}

template<typename T>
void VertexBufferLayout::Push(unsigned int count) 
{
	//static_assert(false);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
	VertexBufferElement element = { GL_FLOAT, count, GL_FALSE };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}
template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	VertexBufferElement element = { GL_UNSIGNED_INT, count, GL_FALSE };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}
template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	VertexBufferElement element = { GL_UNSIGNED_BYTE, count, GL_TRUE };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

std::vector<VertexBufferElement> VertexBufferLayout::GetElements() const
{ 
	return m_Elements; 
}
unsigned int VertexBufferLayout::GetStride() const
{ 
	return m_Stride; 
}