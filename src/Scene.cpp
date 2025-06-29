#include "Scene.hpp"

Scene::Scene(std::string modelName, Vector cameraPos) {
	stateName = SceneState;
    
    parseModel(modelName);
    if (material.isMaterial)
        parseMaterial();
    
    colors.push_back(Vector(1.0f, 0.0f, 0.0f)); // Red
    colors.push_back(Vector(0.0f, 1.0f, 0.0f)); // Green
    colors.push_back(Vector(0.0f, 0.0f, 1.0f)); // Blue
    colors.push_back(Vector(1.0f, 1.0f, 0.0f)); // Yellow
    colors.push_back(Vector(1.0f, 0.0f, 1.0f)); // Magenta
    colors.push_back(Vector(0.0f, 1.0f, 1.0f)); // Cyan
    colors.push_back(Vector(1.0f, 0.5f, 0.0f)); // Orange

    int colorIndex = 0;
    for (const Face &face : mesh.faces) {
        Vertex v1, v2, v3;
        
        v1.position = mesh.vertices[face.v1.v - 1];
        v2.position = mesh.vertices[face.v2.v - 1];
        v3.position = mesh.vertices[face.v3.v - 1];

        Vector faceColor = colors[colorIndex % colors.size()];
        v1.color = faceColor;
        v2.color = faceColor;
        v3.color = faceColor;

        if (!mesh.textureCoord.empty() && face.v1.isText)
            v1.texCoord = mesh.textureCoord[face.v1.vt - 1];
        else
            v1.texCoord = Vector2(0.0f, 0.0f);
        if (face.v2.isText)
            v2.texCoord = mesh.textureCoord[face.v2.vt - 1];
        else
            v2.texCoord = Vector2(1.0f, 0.0f);
        if (face.v3.isText)
            v3.texCoord = mesh.textureCoord[face.v3.vt - 1];
        else
            v3.texCoord = Vector2(1.0f, 1.0f);
        
    
        if (!face.v1.isNormal || !face.v2.isNormal || !face.v3.isNormal)
        {
            Vector normal = (v2.position - v1.position).crossProduct(v3.position - v1.position);
            normal.normalize();

            v1.normal = normal;
            v2.normal = normal;
            v3.normal = normal;
        }
        else if (!mesh.normals.empty()){
            v1.normal = mesh.normals[face.v1.vn - 1];
            v2.normal = mesh.normals[face.v2.vn - 1];
            v3.normal = mesh.normals[face.v3.vn - 1];
        }

        vertexBuffer.push_back(v1);
        vertexBuffer.push_back(v2);
        vertexBuffer.push_back(v3);
        
        colorIndex++;
    }
    for (const Vertex v : vertexBuffer) {
    }
    // Getting model's center
    Vector min = mesh.vertices[0];
    Vector max = mesh.vertices[0];
    for (const Vector &vec : mesh.vertices) {
        min.x = std::min(min.x, vec.x);
        min.y = std::min(min.y, vec.y);
        min.z = std::min(min.z, vec.z);
        max.x = std::max(max.x, vec.x);
        max.y = std::max(max.y, vec.y);
        max.z = std::max(max.z, vec.z);
    }
    center = (min + max) / 2.0f;
    #ifdef _WIN32
        shader = new Shader("C:\\Users\\asus\\Documents\\scop\\shaders\\VertexShader.glsl", "C:\\Users\\asus\\Documents\\scop\\shaders\\FragmentShader.glsl");
    #elif __APPLE__
        shader = new Shader("./shaders/VertexShader.glsl", "./shaders/FragmentShader.glsl");
    #elif __linux__
        shader = new Shader("./shaders/VertexShader.glsl", "./shaders/FragmentShader.glsl");
    #endif
    shader->compileShader(GL_VERTEX_SHADER);
    shader->compileShader(GL_FRAGMENT_SHADER);
    shader->createShader();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), vertexBuffer.data(), GL_STATIC_DRAW);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_Surface *image = TextureLoader::getInstance()->getImage(textureIndex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity(); 
    projection.perspective(Vulpes3D::to_radians(45.0f), 1280.0f / 640.0f, 0.1f, 100.0f);
    
    model.translate(center);

    shader->setUniform("material.ambient", material.Ka);
    shader->setUniform("material.diffuse", material.Kd);
    shader->setUniform("material.specular", material.Ks);
    shader->setUniform("material.shininess", material.Ns);
    shader->setUniform("lightColor", Vector(1.0f, 1.0f, 1.0f));
    shader->setUniform("lightDir", Vector(-0.2f, -1.0f, -0.3f));
    shader->setUniform("flatColor", colors[0]);
    shader->setUniform("blend", blend);
    shader->setUniform("normalColoring", normalColoring);
    shader->setUniform("viewPos", cameraPos);
    shader->setUniform("texture1", 0);

    modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");
    viewLoc = shader->getUniformLoc("view");

    // Verticies
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    // Color
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);
}

Scene::~Scene(void) {
    delete shader;
}

void    Scene::parseModel(std::string &modelName) {
    std::string filePath = "assets/models/" + modelName + ".obj";

    #ifdef _WIN32
        filePath = "C:\\Users\\asus\\Documents\\scop\\assets\\models\\" + modelName + ".obj";
    #endif

    std::ifstream file(filePath.c_str());

    if (!file.is_open())
        throw(ErrorHandler("Failed to open model file: " + std::string(filePath.c_str()), __FILE__, __LINE__));
    
    std::string line;
    while (std::getline(file, line))
    {
        if (material.name.empty()) {
            std::string first = line.substr(0, line.find(" "));
            if (first == "mtllib")
                material.name = line.substr(line.find(" ") + 1);
        }
        if (line.substr(0, line.find(" ")) == "v") {
            std::istringstream iss(line.substr(1));
            float x, y, z;
            iss >> x;
            iss >> y;
            iss >> z;
            mesh.vertices.push_back(Vector(x, y, z));
        }
        if (line.substr(0, line.find(" ")) == "vt") {
            std::istringstream iss(line.substr(1));
            float x, y;
            iss >> x;
            iss >> y;
            mesh.textureCoord.push_back(Vector2(x, y));
        }
        if (line.substr(0, line.find(" ")) == "vn") {
            std::istringstream iss(line.substr(1));
            float x, y, z;
            iss >> x;
            iss >> y;
            iss >> z;
            mesh.normals.push_back(Vector(x, y, z));
        }
        if (line.substr(0, line.find(" ")) == "usemtl")
            material.isMaterial = true;
        // checks for faces
        if (line.substr(0, line.find(" ")) == "f") {
            std::vector<VertexIndex> result = parseFaceVertex(line.substr(2));
            if (result.size() >= 3) {
                for (size_t index = 1; index < result.size() - 1; ++index) {
                    Face face;
                    face.v1 = result[0];
                    face.v2 = result[index];
                    face.v3 = result[index + 1];
                    mesh.faces.push_back(face);
                }
            }
        }
    }
}

std::vector<VertexIndex>    Scene::parseFaceVertex(std::string line) {
    std::vector <VertexIndex> result;

    std::istringstream iss(line);
    std::string part;

    while (iss >> part) {
        VertexIndex vi;
        size_t firstSlash = part.find('/');
        size_t secondSlash = part.find('/', firstSlash + 1);

        if (firstSlash == std::string::npos) {
            vi.v = std::stoi(part); // f v
            vi.isNormal = false;
            vi.isText = false;
        }
        else if (secondSlash == std::string::npos) {
            // f v/vt
            vi.v = std::stoi(part.substr(0, firstSlash));
            vi.vt = std::stoi(part.substr(firstSlash + 1));
            vi.isNormal = false;
            vi.isText = true;
        }
        else if (secondSlash == firstSlash + 1) {
            // f v//vn
            vi.v = std::stoi(part.substr(0, firstSlash));
            vi.vn = std::stoi(part.substr(secondSlash + 1));
            vi.isNormal = true;
            vi.isText = false;
        }
        else {
            // f v/vt/vn
            vi.v = std::stoi(part.substr(0, firstSlash));
            vi.vt = std::stoi(part.substr(firstSlash + 1, secondSlash - firstSlash - 1));
            vi.vn = std::stoi(part.substr(secondSlash + 1));
            vi.isNormal = true;
            vi.isText = true;
        }
        result.push_back(vi);
    }
    return result;
}

void    Scene::parseMaterial(void) {
    std::string filePath = "./assets/materials/" + material.name;

    #ifdef _WIN32
        filePath = "C:\\Users\\asus\\Documents\\scop\\assets\\materials\\" + modelName + ".obj";
    #endif

    std::ifstream file(filePath.c_str());

    if (!file.is_open())
        throw(ErrorHandler("Failed to open material file: " + std::string(filePath.c_str()), __FILE__, __LINE__));
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;

        iss >> prefix;
        if (prefix == "Ns") {
            iss >> material.Ns;
        }
        else if (prefix == "Ka") {
            iss >> material.Ka.x >> material.Ka.y >> material.Ka.z;
        }
        else if (prefix == "Kd") {
            iss >> material.Kd.x >> material.Kd.y >> material.Kd.z;
        }
        else if (prefix == "Ks") {
            iss >> material.Ks.x >> material.Ks.y >> material.Ks.z;
        }
        else if (prefix == "Ni") {
            iss >> material.Ni;
        }
        else if (prefix == "d") {
            iss >> material.d;
        }
        else if (prefix == "illum") {
            iss >> material.illum;
        }
    }
}
void    Scene::render(Vulpes3D::Matrix4x4 view) {
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    shader->useShader();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.size());
}

void    Scene::update(float deltaTime) {
    float speed = 5.0f;
    float target = textureToggle ? 1.0f : 0.0f;
    float epsilon = 0.01f;
    if (abs(blend - target) > 0.01f) {
        blend += (target - blend) * deltaTime * speed;
        if (std::abs(blend - target) <= epsilon) {
            blend = target;
        }
        std::cout << "blend: " << blend << std::endl;
        shader->setUniform("blend", blend);
    }
}

void    Scene::keyDown(SDL_Scancode key, float deltaTime, InputManager* input, Camera *camera) {
    // (void)deltaTime;
    if (InputDetector::getInstance()->isKeyPressed(key)) {
        if (key == SDL_SCANCODE_I) {
            // std::cout << "rotating on X" << std::endl;
            angle += 5.0f;
            model.translate(-center);
            model = Vulpes3D::Matrix4x4::identity();
            model.rotate(Vector(), X_AXIS, Vulpes3D::to_radians(angle));
            model.translate(center);
        }
        if (key == SDL_SCANCODE_O) {
            angle += 5.0f;
            // std::cout << "rotating on Y" << std::endl;
            model.translate(-center);
            model = Vulpes3D::Matrix4x4::identity();
            model.rotate(Vector(), Y_AXIS, Vulpes3D::to_radians(angle));
            model.translate(center);
        }
        if (key == SDL_SCANCODE_P) {
            // std::cout << "rotating on Z" << std::endl;
            angle += 5.0f;
            model.translate(-center);
            model = Vulpes3D::Matrix4x4::identity();
            model.rotate(Vector(), Z_AXIS, Vulpes3D::to_radians(angle));
            model.translate(center);
        }
        if (key == SDL_SCANCODE_UP) {
            model.translate(Vector(0.0f, deltaTime * 10.0f, 0.0f));
        }
        if (key == SDL_SCANCODE_DOWN) {
            model.translate(Vector(0.0f, -deltaTime * 10.0f, 0.0f));
        }
        if (key == SDL_SCANCODE_RIGHT) {
            model.translate(Vector(deltaTime * 10.0f, 0.0f, 0.0f));
        }
        if (key == SDL_SCANCODE_LEFT) {
            model.translate(Vector(-deltaTime * 10.0f, 0.0f, 0.0f));
        }
        if (key == SDL_SCANCODE_T) {
            textureToggle = !textureToggle;
        }
        if (key == SDL_SCANCODE_N) {
            normalColoring = normalColoring == 0 ? 1 : 0;
            shader->setUniform("normalColoring", normalColoring);
        }
        // Change texture to one of the textures under /assets/textures or change colors
        if (key == SDL_SCANCODE_K) {
            if (textureToggle) {
                SDL_Surface *image = TextureLoader::getInstance()->getImage(textureIndex);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, 
                        GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
                glGenerateMipmap(GL_TEXTURE_2D);
                std::cout << blend << std::endl;
            }
            else {
                colorIndex += 1;
                if (colorIndex == colors.size()) colorIndex = 0;
                shader->setUniform("flatColor", colors[colorIndex]);
                std::cout << blend << std::endl;
            }
        }
        if (key == SDL_SCANCODE_ESCAPE) {
			StatesManager::getInstance()->removeState(input);
			return ;
		}
    }
}

void    Scene::mouseMove(Uint8, InputManager*) {

}

void    Scene::handleInput(void) {

}