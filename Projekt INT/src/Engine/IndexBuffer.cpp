#include "Engine/IndexBuffer.h"
#include "Engine/Renderer.h"

IndexBuffer::IndexBuffer()
{
    GLCall(glGenBuffers(1, &m_Renderer_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_Renderer_ID));
}

void IndexBuffer::LoadData(const unsigned int* data, unsigned int count)
{
    m_Count = count;
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
