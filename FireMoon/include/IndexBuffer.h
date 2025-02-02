#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void LoadData(const unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_Renderer_ID;
	unsigned int m_Count;
};