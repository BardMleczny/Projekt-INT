#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    inline Camera(const Camera&) = delete;
    static Camera& Get();

    void TransformMatrix(float x, float y);
    glm::mat4 GetMatrix() { return view; }

private:
    inline Camera() { view = glm::mat4(1.0f); }

    glm::mat4 view;
};