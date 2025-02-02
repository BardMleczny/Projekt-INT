#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Camera.h"
#include "Color.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line); 

class Rectangle;

class Renderer {
public:
    static void Clear();
    //static void Init();
    //static bool ShouldWindowClose();
    //static void BeginIteration();
    //static void EndIteration();
    //static void Terminate();
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void DrawBatch(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int* indices);
    static void DrawRectangle(const Rectangle& rectangle, const Color& color, Camera& camera, Shader& shader);
    static void DrawRectangle(const Rectangle& rectangle, const Color& color, glm::mat4 view, Shader& shader);
private:
    //static void CalculateFPS();

    //static GLFWwindow* window;
    //static double lastTime;
    //static int frameCount;
};