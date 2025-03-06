#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Shader.hpp"
#include "SDL.h"
#include "SDL_image.h"
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
        unsigned int texture;
};