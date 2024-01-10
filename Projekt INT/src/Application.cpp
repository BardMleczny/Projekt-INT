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

#include "Number.h"

#include "Camera.h"

void calculateFPS(GLFWwindow* window);

double lastTime = 0.0;
int frameCount = 0;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1600, 960, "Projekt", NULL, NULL);

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
        Camera camera;

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        Grid grid("res/textures/map3.png");

        Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        Player player(*new Rectangle(192, 640, 96, 96, "res/shaders/basicRectangle.shader"), color, "res/textures/player_right.png");
        //Player player(*new Rectangle(200, 2400, 96, 96, "res/shaders/basicRectangle.shader"), color, "res/textures/player_right.png"); 
        //NumberText n(251, 64);

        std::vector<GameObject*> f;
        for (int i = 0; i < grid.size; i++)
        {
            //std::cout << grid.tiles[i].type;
            /*if (grid.tiles[i].type != TerrainType::SKY && grid.tiles[i].type != TerrainType::DEFAULT)
            {
                Transform t = grid.tiles[i].transform;
                
                f.emplace_back(new GameObject(*new Rectangle(t.x, t.y, t.width, t.height, "res/shaders/basic.shader"), { 0.0f, 0.0f, 0.0f, 1.0f }, "res/textures/image1.png"));
            }*/
        }

        while (!glfwWindowShouldClose(window))
        {
            calculateFPS(window);

            renderer.Clear();
            player.Update(renderer, grid, camera);
            grid.Draw(renderer, camera.GetMatrix());

            /*for (int i = 0; i < f.size(); i++)
            {
                f[i]->Draw(renderer);
            }*/

            

            //n.Draw(100, 100, renderer);

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

void calculateFPS(GLFWwindow* window) {
    double currentTime = glfwGetTime();

    double deltaTime = currentTime - lastTime;

    frameCount++;

    if (deltaTime >= 1.0) {
        double fps = static_cast<double>(frameCount) / deltaTime;
        std::cout << "FPS: " << fps << std::endl;

        frameCount = 0;
        lastTime = currentTime;
    }
}