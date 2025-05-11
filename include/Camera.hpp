#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Matrix.hpp"

class Camera {
    public:
        Camera(void);
        ~Camera(void);
        // Vulpes3D::Matrix4x4 &lookAt(Vector &target);
        float *getView(void);
    private:
        Vector cameraPos;
        Vector cameraDirection;
        Vector cameraRight;
        Vector cameraUp;
        Vulpes3D::Matrix4x4 view;
};