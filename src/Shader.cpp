#include "Shader.hpp"

Shader::Shader(void)
{
    loadShader("C:\\Users\\asus\\Documents\\scop\\shaders\\VertexShader.glsl", GL_VERTEX_SHADER);
    loadShader("C:\\Users\\asus\\Documents\\scop\\shaders\\FragmentShader.glsl", GL_FRAGMENT_SHADER);
}

Shader::~Shader(void)
{
    glDeleteProgram(shaderProgram);
}

// std::string Shader::getShaderPath(std::string filename) {
//     std::filesystem::path currPath = std::filesystem::current_path();

//     return (currPath / "shaders" / filename).string();
// }

void Shader::loadShader(const char *filepath, GLenum shaderType) {
    std::ifstream file(filepath);

    if (!file.is_open())
        throw(ErrorHandler("Failed to open shader file: " + std::string(filepath), __FILE__, __LINE__));
     std::string source( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );

    if (shaderType == GL_VERTEX_SHADER)
        vertexSource = source;
    else
        fragmentSource = source;
    file.close();
}

void Shader::compileShader(GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    std::string shaderSource = shaderType == GL_VERTEX_SHADER ? vertexSource : fragmentSource;
    const char *shaderSourceStr = shaderSource.c_str();

    glShaderSource(shader, 1, &shaderSourceStr, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw(ErrorHandler("Error shader vertex compilation failed: " + std::string(infoLog), __FILE__, __LINE__));
    }
    if (shaderType == GL_VERTEX_SHADER)
        vertexShader = shader;
    else
        fragmentShader = shader;
}

void    Shader::createShader(void) {
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw(ErrorHandler("Shader program link failed: " + std::string(infoLog), __FILE__, __LINE__));
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void    Shader::setUniform(const char *uniform, GLint id) {
    glUniform1i(glGetUniformLocation(shaderProgram, uniform), id);
}

void    Shader::setUniform(const char *uniform, const Vector &vec) {
    GLint location = glGetUniformLocation(shaderProgram, uniform);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

unsigned int Shader::getUniformLoc(const char *uniform) {
    return glGetUniformLocation(shaderProgram, uniform);
}

void    Shader::useShader(void) {
    glUseProgram(shaderProgram);
}