#pragma once

#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count);

	template<>
	void Push<float>(unsigned int count);
	template<>
	void Push<unsigned int>(unsigned int count);
	template<>
	void Push<unsigned char>(unsigned int count);

	std::vector<VertexBufferElement> GetElements() const;
	unsigned int GetStride() const;
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};