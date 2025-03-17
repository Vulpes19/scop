#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Shader.hpp"
#include "SDL.h"
#include "TextureLoader.hpp"
#include "Matrix.hpp"

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
        Matrix4x4   transform;
        unsigned int   transformLoc;
};