#pragma once

#include <iostream>
#include <fstream>
#include "ErrorHandler.hpp"
#include <string>
#include "Vector.hpp"
#include "./glad/glad.h"
// #include <filesystem>

class Shader {
    public:
        Shader(void);
        ~Shader(void);
        void    loadShader(const char *, GLenum);
        void    compileShader(GLenum);
        void    createShader(void);
        void    setUniform(const char *uniform, GLint);
        void    setUniform(const char *uniform, const Vector &);
        void    setUniform(const char *uniform, const float);
        unsigned int getUniformLoc(const char *uniform); 
        void    useShader(void);
    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;
        std::string vertexSource;
        std::string fragmentSource;
};