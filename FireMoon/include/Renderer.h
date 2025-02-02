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
    inline Renderer(const Renderer&) = delete;
    static Renderer& Get();

    static inline void Clear() { Get().IClear(); }
    static inline bool ShouldWindowClose() { return Get().IShouldWindowClose(); }
    static inline void Init() { Get().IInit(); }
    static inline void BeginIteration() { Get().IBeginIteration(); }
    static inline void EndIteration() { Get().IEndIteration(); }
    static inline void Terminate() { Get().ITerminate(); }
    static inline void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) { Get().IDraw(va, ib, shader); }
    static inline void DrawBatch(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int* indices) { Get().IDrawBatch(va, ib, shader, indices); }
    static inline void DrawRectangle(const Rectangle& rectangle, const Color& color, Shader& shader) { Get().IDrawRectangle(rectangle, color, shader); }
    static inline void DrawRectangle(const Rectangle& rectangle, const Color& color, glm::mat4 view, Shader& shader) { Get().IDrawRectangle(rectangle, color, view, shader); }

    int frameCount;

private:
    Renderer();

    void IClear();
    bool IShouldWindowClose();
    void IInit();
    void IBeginIteration();
    void IEndIteration();
    void ITerminate();
    void IDraw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void IDrawBatch(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int* indices);
    void IDrawRectangle(const Rectangle& rectangle, const Color& color, Shader& shader);
    void IDrawRectangle(const Rectangle& rectangle, const Color& color, glm::mat4 view, Shader& shader);

    void CalculateFPS();

    GLFWwindow* window;
    double lastTime;
};