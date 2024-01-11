#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void LoadData(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_Renderer_ID;
};