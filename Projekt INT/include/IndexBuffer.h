#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer();
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_Renderer_ID;
	unsigned int m_Count;
};