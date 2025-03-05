#include "Object.hpp"

Object::Object(void) {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f  // Top
    };
    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // the buffer type of a vertex buffer is GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy vertex data to vertex buffer

    shader = new Shader();
    shader->compileShader(GL_VERTEX_SHADER);
    shader->compileShader(GL_FRAGMENT_SHADER);
    shader->createShader();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //texture generating
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        throw(ErrorHandler("Error failed to init SDL_image: " + std::string(IMG_GetError()), __FILE__, __LINE__));
    }
    SDL_Surface* image = IMG_Load("C:\\Users\\asus\\Documents\\scop\\assets\\green.png");
    if (!image) {
        std::cout << IMG_GetError() << std::endl;
        throw(ErrorHandler("Error failed to load image: " + std::string(IMG_GetError()), __FILE__, __LINE__));
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(image);
    //texture generation

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

Object::~Object(void) {

}

void    Object::render(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader->getShaderProgram());
    glBindTexture(GL_TEXTURE_2D, texture);
    // float timeValue = SDL_GetTicks();
    // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(shader->getShaderProgram(), "ourColor");
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

void    Object::update(void) {
    
}