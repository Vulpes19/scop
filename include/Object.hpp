#pragma once

#ifdef _WIN32
#include "./glad/glad.h"
#elif __APPLE__
#include "glad.h"
#endif
#include <iostream>
#include "Shader.hpp"
#include "SDL.h"
#include "TextureLoader.hpp"
#include "Matrix.hpp"
#include <vector>
#include "Camera.hpp"

class Object {
    public:
        Object(void);
        ~Object(void);
        void render(Vulpes3D::Matrix4x4 view);
        void update(void);
    private:
        unsigned int VBO; //vertex buffer object we need to store verticies in GPU memory
        Shader      *shader;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int texture1;
        unsigned int texture2;
        Vulpes3D::Matrix4x4   model;
        Vulpes3D::Matrix4x4   view2;
        // glm::mat4   model;
        // glm::mat4   view2;
        Vulpes3D::Matrix4x4   projection;
        // glm::mat4 projection;
        unsigned int   modelLoc;
        unsigned int   projectionLoc;
        unsigned int   viewLoc;
        std::vector<Vector> cubePositions;
};