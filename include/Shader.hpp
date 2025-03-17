#pragma once

#include <iostream>
#include <fstream>
#include "ErrorHandler.hpp"
#include <string>
#include "./glad/glad.h"
// #include <filesystem>

class Shader {
    public:
        Shader(void);
        ~Shader(void);
        // std::string getShaderPath(std::string);
        void    loadShader(const char *, GLenum);
        void    compileShader(GLenum);
        void    createShader(void);
        void    setUniform(const char *uniform, GLint);
        void    useShader(void);
    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;
        std::string vertexSource;
        std::string fragmentSource;
};