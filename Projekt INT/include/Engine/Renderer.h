#pragma once

#include <GL/glew.h>

#include "Engine/VertexArray.h"
#include "Engine/IndexBuffer.h"
#include "Engine/Shader.h"

#include "Engine/Camera.h"
#include "Engine/Color.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line); 

class Rectangle;

class Renderer {
public:
    Renderer();

    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawBatch(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int* indices) const;
    void DrawRectangle(const Rectangle& rectangle, const Color& color, Shader& shader, glm::mat4 view = glm::mat4(1.0f)) const;
private:
    
};