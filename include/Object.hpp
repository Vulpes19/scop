#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Shader.hpp"
#include "SDL.h"
#include "TextureLoader.hpp"
#include "Matrix.hpp"
#include <vector>

class Object {
    public:
        Object(void);
        ~Object(void);
        void render(void);
        void update(void);
    private:
        unsigned int VBO; //vertex buffer object we need to store verticies in GPU memory
        Shader      *shader;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int texture1;
        unsigned int texture2;
        Vulpes3D::Matrix4x4   model;
        Vulpes3D::Matrix4x4   view;
        // glm::mat4   model;
        // glm::mat4   view;
        Vulpes3D::Matrix4x4   projection;
        // glm::mat4 projection;
        unsigned int   modelLoc;
        unsigned int   projectionLoc;
        unsigned int   viewLoc;
        std::vector<Vector> cubePositions;
};