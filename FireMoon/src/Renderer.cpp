#include "Renderer.h"

#include <iostream>


#include "Rectangle.h"
#include "Input.h"

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
    : m_lastTime(1.0), m_frameCount(1)
{
    
}

void Renderer::IInit()
{
    if (!glfwInit())
        __debugbreak;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(1600, 960, "Projekt", NULL, NULL);

    Input::window = m_window;

    if (!m_window)
    {
        glfwTerminate();
        __debugbreak;
    }

    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Renderer& Renderer::Get()
{
    static Renderer renderer;
    return renderer;
}

void Renderer::IClear()
{
    glClearColor(0.15, 0.67, 0.88, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}


bool Renderer::IShouldWindowClose()
{
    return glfwWindowShouldClose(m_window) || Input::isKeyPressed(GLFW_KEY_ESCAPE);
}

void Renderer::IBeginIteration()
{
    CalculateFPS();

    Renderer::Clear();
}


void Renderer::CalculateFPS() {
    double currentTime = glfwGetTime();

    m_deltaTime = currentTime - m_lastTime;
    //std::cout << m_deltaTime << std::endl;
    m_frameCount++;

    if (((int)(1 / m_deltaTime) - m_frameCount) <= 0) {
        double fps = 1 / m_deltaTime;
        std::cout << "FPS: " << fps << std::endl;
        std::cout << "Delta: " << GetDeltaTime() << std::endl;



        m_frameCount = 0; 
    }
    m_lastTime = currentTime;
}

void Renderer::IEndIteration()
{
    glfwSwapBuffers(m_window);

    glfwPollEvents();
}

void Renderer::ITerminate()
{
    glfwTerminate();
}

void Renderer::IDraw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::IDrawBatch(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int* indices)
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, indices));
}

void Renderer::IDrawRectangle(const Rectangle& rectangle, const Color& color, Shader& shader)
{
    glm::mat4 proj = glm::ortho(0.0f, 1600.0f, 0.0f, 960.0f, -1.0f, 1.0f);
    glm::mat4 view = Camera::GetMatrix();
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

void Renderer::IDrawRectangle(const Rectangle& rectangle, const Color& color, glm::mat4 view, Shader& shader)
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

