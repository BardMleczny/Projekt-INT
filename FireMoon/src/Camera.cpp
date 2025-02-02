#include "Camera.h"

Camera& Camera::Get()
{
	static Camera camera;
	return camera;
}

void Camera::ITransformMatrix(float x, float y)
{
	view = glm::translate(glm::mat4(1.0f), glm::vec3(800 - x, 480 - y, 0));
}
