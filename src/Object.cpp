#include "Object.hpp"

Object::Object(void) {
    
//     float vertices[] = {
//         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
//         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // top left 
//    };
cubePositions.push_back(Vector( 0.0f,  0.0f,  0.0f));
cubePositions.push_back(Vector( 2.0f,  5.0f, -15.0f));
cubePositions.push_back(Vector(-1.5f, -2.2f, -2.5f)); 
cubePositions.push_back(Vector(-3.8f, -2.0f, -12.3f));  
cubePositions.push_back(Vector( 2.4f, -0.4f, -3.5f));
cubePositions.push_back(Vector(-1.7f,  3.0f, -7.5f));  
cubePositions.push_back(Vector( 1.3f, -2.0f, -2.5f));  
cubePositions.push_back(Vector( 1.5f,  2.0f, -2.5f)); 
cubePositions.push_back(Vector( 1.5f,  0.2f, -1.5f)); 
cubePositions.push_back(Vector(-1.3f,  1.0f, -1.5f));
float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
    
    size_t i = 0;
    SDL_Surface *image = TextureLoader::getInstance()->getImage(i);
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
    image = TextureLoader::getInstance()->getImage(i);
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

    
    // model = Vulpes3D::Matrix4x4::identity();
    // model.scale(Vector(0.5f, 0.5f, 1.0f));
    // transform.translate(Vector(0.2f, -0.2f, 0.0f));
    // model.rotate(Vector(0.2f, -0.2f, 0.0f), X_AXIS, Vulpes3D::to_radians(30.0f));

    // projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    
    // view = Vulpes3D::Matrix4x4::identity();
    // view.translate(Vector(0.0f, 0.0f, -3.0f));

    
    
    // model = Vulpes3D::Matrix4x4::identity();
    view2 = Vulpes3D::Matrix4x4::identity();
    projection = Vulpes3D::Matrix4x4::identity();
    
    projection.perspective(Vulpes3D::to_radians(45.0f), 1280.0f / 640.0f, 0.1f, 100.0f);
    // view.translate(Vector(0.0f, 0.0f, -3.0f));
    // model.rotate(Vector(0.2f, -0.2f, 0.0f), X_AXIS,  Vulpes3D::to_radians(-55.0f));
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // view          = glm::mat4(1.0f);
    // projection    = glm::mat4(1.0f);
    
    // projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    // view  = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
    // model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
    
    modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");
    viewLoc = shader->getUniformLoc("view");
}

Object::~Object(void) {
    
}

void    Object::render(Vulpes3D::Matrix4x4 view) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    
    shader->useShader();

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.data()); //OpenGL expects matrix in Column major "GL_TRUE"
   
    glBindVertexArray(VAO);
    for (size_t i = 0; i < cubePositions.size(); i++) {
        model = Vulpes3D::Matrix4x4::identity();
        float angle = i * 20.0f;
        model.translate(cubePositions[i]);
        model.rotate(Vector(1.0f, 0.0f, 0.0f), X_AXIS, Vulpes3D::to_radians(angle));
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.data()); //OpenGL expects matrix in Column major "GL_TRUE"
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void    Object::update(void) {

    // model = Vulpes3D::Matrix4x4::identity();
    // model.rotate(Vector(0.0f, 0.0f, 1.0f), X_AXIS, time);
}