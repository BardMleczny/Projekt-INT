#include "Camera.h"

Camera::Camera()
{
	view = glm::mat4(1.0f);
}

void Camera::TransformMatrix(float x, float y)
{
	view = glm::translate(glm::mat4(1.0f), glm::vec3(800 - x, 480 - y, 0));
}
