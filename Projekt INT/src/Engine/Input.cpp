#include "Engine/Input.h"

GLFWwindow* Input::window = nullptr;

bool Input::isKeyPressed(int keyCode)
{
    return (glfwGetKey(window, keyCode) == GLFW_PRESS);
}

bool Input::isKeyDown(int keyCode)
{
    return (glfwGetKey(window, keyCode) == GLFW_PRESS) || (glfwGetKey(window, keyCode) == GLFW_REPEAT);
}

bool Input::isKeyReleased(int keyCode)
{
    return (glfwGetKey(window, keyCode) == GLFW_RELEASE);
}
