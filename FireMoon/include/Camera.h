#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    inline Camera(const Camera&) = delete;
    static Camera& Get();
    
    static inline void TransformMatrix(float x, float y) { Camera::Get().ITransformMatrix(x, y); }
    static inline glm::mat4 GetMatrix() { return Get().IGetMatrix(); }

    private:
        void ITransformMatrix(float x, float y);
        glm::mat4 IGetMatrix() { return view; }
        inline Camera() { view = glm::mat4(1.0f); }

    glm::mat4 view;
};