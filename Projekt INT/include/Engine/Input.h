#pragma once

#include "GLFW/glfw3.h"

static class Input
{
public:
	static bool isKeyPressed(int keyCode);
	static bool isKeyDown(int keyCode);
	static bool isKeyReleased(int keyCode);
	static GLFWwindow* window;
};
