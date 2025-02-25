#pragma once

#include "./glad/glad.h"
#include <iostream>

class Object {
    public:
        Object(void);
        ~Object(void);
        void render(void);
        void update(void);
    private:
        unsigned int VBO; //vertex buffer object we need to store verticies in GPU memory
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;
        unsigned int VAO;
};