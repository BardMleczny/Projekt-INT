#include "Renderer.h"

#include <iostream>

#include "Rectangle.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    : basicRectangleShader("res/shaders/basicRectangle.shader")
{
}

void Renderer::Clear() 
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawRectangle(const Rectangle& rectangle, Color color)
{
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(rectangle.m_x, rectangle.m_y, 0));

    glm::mat4 mvp = proj * view * model;

    basicRectangleShader.Bind();
    basicRectangleShader.SetUniformMat4f("u_MVP", mvp);
    basicRectangleShader.SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

    rectangle.GetVA().Bind();
    rectangle.GetIB().Bind();

    GLCall(glDrawElements(GL_TRIANGLES, rectangle.GetIB().GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawRectangle(const Rectangle& rectangle, const Color& color, Shader shader)
{
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(rectangle.m_x, rectangle.m_y, 0));

    glm::mat4 mvp = proj * view * model;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);
    shader.SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

    rectangle.GetVA().Bind();
    rectangle.GetIB().Bind();

    GLCall(glDrawElements(GL_TRIANGLES, rectangle.GetIB().GetCount(), GL_UNSIGNED_INT, nullptr));
}
