#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer()
{
    GLCall(glGenBuffers(1, &m_Renderer_ID));
}

void VertexBuffer::LoadData(const void* data, unsigned int size)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_Renderer_ID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
