#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Input.h"

#include "Rectangle.h"
#include "Player.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../tests/TestClearColor.h"

#include "Grid.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(960, 720, "Projekt", NULL, NULL);

    Input::window = window;

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

<<<<<<< Updated upstream
        Grid grid("res/textures/test_map.png");

        Rectangle rectangle(100, 100, 100, 100, "res/shaders/basicRectangle.shader");
        Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        Player player(rectangle, color, "res/textures/image1.png");
        
        //Rectangle rectangle1(100, 100, 100, 100, "res/shaders/basicRectangle.shader");
=======
        Color color = { 0.0f, 1.0f, 0.0f, 1.0f };
        //Player player(*new Rectangle(100, 100, 100, 100, "res/shaders/basicRectangle.shader"), color, "res/textures/image1.png");

        VertexArray va;
        float buffer[] = {
            0.0f,      0.0f,       0.0f, 0.0f,
            100.0f,    0.0f,       1.0f, 0.0f,
            100.0f,    100.0f,     1.0f, 1.0f,
            0.0f,      100.0f,     0.0f, 1.0f,

            200.0f,    200.0f,     0.0f, 0.0f,
            300.0f,    200.0f,     1.0f, 0.0f,
            300.0f,    300.0f,     1.0f, 1.0f,
            200.0f,    300.0f,     0.0f, 1.0f
        };

        VertexBuffer vb;
        vb.LoadData(buffer, 32);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        unsigned int vertices[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4
        };

        IndexBuffer ib(vertices, 12);

        Shader shader("res/shaders/basic.shader");

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 mvp = proj;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        shader.SetUniform4f("u_Color", 1.0f, 0.0f, 1.0f, 1.0f);
>>>>>>> Stashed changes

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

<<<<<<< Updated upstream
            grid.Draw(renderer);
            player.Draw(renderer);
=======
            //player.Draw(renderer);
            
            renderer.Draw(va, ib, shader);
>>>>>>> Stashed changes

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    glfwTerminate();
    return 0;
}


        /*  
        VertexArray va;
        float buffer[] = {
            0.0f,    0.0f,     0.0f, 0.0f,
            100.0f,  0.0f,     1.0f, 0.0f,
            100.0f,  100.0f,   1.0f, 1.0f,
            0.0f,    100.0f,   0.0f, 1.0f
        };

        VertexBuffer vb;
        vb.LoadData(buffer, 16);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        unsigned int vertices[] = {
            0, 1, 2,
            2, 3, 0
        };

        IndexBuffer ib(vertices, 6);

        Shader shader("res/shaders/basic.shader");

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 mvp = proj;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        shader.SetUniform4f("u_Color", 1.0f, 0.0f, 1.0f, 1.0f);
        */

        //renderer.Draw(va, ib, shader);
