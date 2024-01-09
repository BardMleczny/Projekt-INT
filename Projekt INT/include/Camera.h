#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera();

	void TransformMatrix(float x, float y);
	inline glm::mat4 GetMatrix() { return view; };
private:
	glm::mat4 view;
};
