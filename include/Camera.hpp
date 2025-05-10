#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Matrix.hpp"

class Camera {
    public:
        Camera(void);
        ~Camera(void);
    private:
        Vector cameraPos;
        Vector cameraDirection;
        Vector cameraRight;
};