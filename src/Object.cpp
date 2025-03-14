#include "Object.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image/stb_image.h"

Object::Object(void) {
    // float vertices[] = {
    //     // Positions       // Colors       // Texture Coords (U, V)
    //     -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
    //     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
    //     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f  // Top-center
    // };
    float vertices[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // top left 
   };
   unsigned int indices[] = {  // note that we start from 0!
       0, 1, 3,   // first triangle
       1, 2, 3    // second triangle
   };

   shader = new Shader();
   shader->compileShader(GL_VERTEX_SHADER);
   shader->compileShader(GL_FRAGMENT_SHADER);
   shader->createShader();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind and upload VBO data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and upload EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //texture generating
    TextureLoader::getInstance()->loadImage("C:\\Users\\asus\\Documents\\scop\\assets\\brick.png");
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification
    
    SDL_Surface *image = TextureLoader::getInstance()->getImage("brick");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    // texture 2 
    TextureLoader::getInstance()->loadImage("C:\\Users\\asus\\Documents\\scop\\assets\\cracks.png");
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification
    
    SDL_FreeSurface(image);
    image = TextureLoader::getInstance()->getImage("cracks");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, 
             GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    //texture generation
    
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    
    shader->useShader();
    shader->setUniform("texture1", 0);
    shader->setUniform("texture2", 1);
}

Object::~Object(void) {

}

void    Object::render(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // int vertexColorLocation = glGetUniformLocation(shader->getShaderProgram(), "ourColor");
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    shader->useShader();
    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void    Object::update(void) {
    
}