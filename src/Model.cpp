#include "Model.hpp"

Model::Model(std::string modelName) {
    parseModel(modelName);
    if (material.isMaterial)
        parseMaterial();
    
    std::cout << mesh.vertices.size() << std::endl;
    for (const Face &face : mesh.faces) {
        Vertex v1, v2, v3;
        
        v1.position = mesh.vertices[face.v1.v - 1];
        if (face.v1.vt > 0)
            v1.texCoord = mesh.textureCoord[face.v1.vt - 1];
        if (face.v1.vn > 0)
            v1.normal = mesh.normals[face.v1.vn - 1];
        // std::cout << "hello" << std::endl;
        
        v2.position = mesh.vertices[face.v2.v - 1];
        if (face.v2.vt > 0)
            v2.texCoord = mesh.textureCoord[face.v2.vt - 1];
        if (face.v2.vn > 0)
            v2.normal = mesh.normals[face.v2.vn - 1];
        // std::cout << "hello2" << std::endl;
        
        v3.position = mesh.vertices[face.v3.v - 1];
        if (face.v3.vn > 0)
            v3.normal = mesh.normals[face.v3.vn - 1];
        // std::cout << "hello3" << std::endl;

        vertexBuffer.push_back(v1);
        vertexBuffer.push_back(v2);
        vertexBuffer.push_back(v3);
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

    shader = new Shader();
    shader->compileShader(GL_VERTEX_SHADER);
    shader->compileShader(GL_FRAGMENT_SHADER);
    shader->createShader();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(vertexBuffer), vertexBuffer.data(), GL_STATIC_DRAW);
    
    projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity();
    
    projection.perspective(Vulpes3D::to_radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    model.translate(center);

    modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");
    viewLoc = shader->getUniformLoc("view");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
}

Model::~Model(void) {
    delete shader;
}

void    Model::parseModel(std::string &modelName) {
    std::string filePath = "C:\\Users\\asus\\Documents\\scop\\assets\\models\\" + modelName + ".obj";

    std::ifstream file(filePath.c_str());

    if (!file.is_open())
        throw(ErrorHandler("Failed to open model file: " + std::string(filePath.c_str()), __FILE__, __LINE__));
    
    std::string line;
    while (std::getline(file, line))
    {
        if (material.name.empty()) {
            std::string first = line.substr(0, line.find(" "));
            std::cout << "first => " << first << std::endl;
            if (first == "mtllib")
            {
                material.name = line.substr(line.find(" ") + 1);
                std::cout << "material name => " << material.name << std::endl;
            }
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
                    // std::cout << face.v1.v << " " << face.v2.v << " " << face.v3.v << std::endl;
                    mesh.faces.push_back(face);
                    // if (mesh.faces.size() > 3)
                    //     exit(1);
                }
            }
        }
    }
}

std::vector<VertexIndex>    Model::parseFaceVertex(std::string &line) {
    std::vector <VertexIndex> result;

    std::istringstream iss(line);
    std::string part;

    while (iss >> part) {
        VertexIndex vi;
        size_t firstSlash = part.find('/');
        size_t secondSlash = part.find('/', firstSlash + 1);

        if (firstSlash == std::string::npos)
            vi.v = std::stoi(part); // f v
        else if (secondSlash == std::string::npos) {
            // f v/vt
            vi.v = std::stoi(part.substr(0, firstSlash));
            vi.vt = std::stoi(part.substr(firstSlash + 1));
        }
        else if (secondSlash == firstSlash + 1) {
            // f v//vn
            vi.v = std::stoi(part.substr(0, firstSlash));
            vi.vn = std::stoi(part.substr(secondSlash + 1));
        }
        else {
            // f v/vt/vn
            vi.v = std::stoi(part.substr(0, firstSlash));
            vi.vt = std::stoi(part.substr(firstSlash + 1, secondSlash - firstSlash - 1));
            vi.vn = std::stoi(part.substr(secondSlash + 1));
        }
        result.push_back(vi);
    }
    return result;
}

void    Model::parseMaterial(void) {
    std::string filePath = "C:\\Users\\asus\\Documents\\scop\\assets\\materials\\" + material.name;

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
            std::cout << material.Ns << std::endl;
        }
        else if (prefix == "Ka") {
            iss >> material.Ka.x >> material.Ka.y >> material.Ka.z;
            std::cout << material.Ka.x << " " << material.Ka.y << " " << material.Ka.z << std::endl;
        }
        else if (prefix == "Kd") {
            iss >> material.Kd.x >> material.Kd.y >> material.Kd.z;
            std::cout << material.Kd.x << " " << material.Kd.y << " " << material.Kd.z << std::endl;
        }
        else if (prefix == "Ks") {
            iss >> material.Ks.x >> material.Ks.y >> material.Ks.z;
            std::cout << material.Ks.x << " " << material.Ks.y << " " << material.Ks.z << std::endl;
        }
        else if (prefix == "Ni") {
            iss >> material.Ni;
            std::cout << material.Ni << std::endl;
        }
        else if (prefix == "d") {
            iss >> material.d;
            std::cout << material.d << std::endl;
        }
        else if (prefix == "illum") {
            iss >> material.illum;
            std::cout << material.illum << std::endl;
        }
    }
}
void    Model::render(Vulpes3D::Matrix4x4 view) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->useShader();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.data()); //OpenGL expects matrix in Column major "GL_TRUE"
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.size());
}

void    Model::update() {

}

void    Model::keyDown(SDL_Scancode key, float deltaTime, InputManager *input) {
    if (InputDetector::getInstance()->isKeyPressed(key)) {
        if (key == SDL_SCANCODE_I) {
            std::cout << "rotating on X" << std::endl;
            angle += 5.0f;
            model.translate(-center);
            model.identity();
            model.rotate(Vector(), X_AXIS, Vulpes3D::to_radians(angle));
            model.translate(center);
        }
        if (key == SDL_SCANCODE_O) {
            angle += 5.0f;
            std::cout << "rotating on Y" << std::endl;
            model.translate(-center);
            model.identity();
            model.rotate(Vector(), Y_AXIS, Vulpes3D::to_radians(angle));
            model.translate(center);
        }
        if (key == SDL_SCANCODE_P) {
            std::cout << "rotating on Z" << std::endl;
            angle += 5.0f;
            model.translate(-center);
            model.identity();
            model.rotate(Vector(), Z_AXIS, Vulpes3D::to_radians(angle));
            model.translate(center);
        }
    }
}

void    Model::mouseMove(Uint8, InputManager*) {

}