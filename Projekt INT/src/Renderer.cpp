#include "Renderer.h"

#include <iostream>

#include "Rectangle.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer()
{
}

void Renderer::Clear()
{
    glClearColor(0.15, 0.67, 0.88, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawBatch(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int* indices) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, indices));
}

void Renderer::DrawRectangle(const Rectangle& rectangle, const Color& color, Shader& shader, glm::mat4 view) const
{
    glm::mat4 proj = glm::ortho(0.0f, 1600.0f, 0.0f, 960.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(rectangle.m_transform.x, rectangle.m_transform.y, 0));

    glm::mat4 mvp = proj * view * model;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);
    shader.SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

    rectangle.m_va.Bind();
    rectangle.m_ib.Bind();

    unsigned int vertices[] = {
            0, 1, 2,
            2, 3, 0
    };

    GLCall(glDrawElements(GL_TRIANGLES, rectangle.m_ib.GetCount(), GL_UNSIGNED_INT, &vertices));
}

