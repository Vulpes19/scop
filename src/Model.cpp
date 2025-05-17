#include "Model.hpp"

Model::Model(std::string modelName) {
    parseModel(modelName);
    if (material.isMaterial)
        parseMaterial();
    
    for (const Face &face : mesh.faces) {
        for (const VertexIndex &vi : face.vertices) {

        }
    }
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
            float x, y, z;
            iss >> x;
            iss >> y;
            iss >> z;
            mesh.textureCoord.push_back(Vector(x, y, z));
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
    shader = new Shader();
    shader->compileShader(GL_VERTEX_SHADER);
    shader->compileShader(GL_FRAGMENT_SHADER);
    shader->createShader();
 
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);
 
     glBindVertexArray(VAO);
}

void    Model::update() {

}

void    Model::keyDown(SDL_Scancode, float, InputManager *) {

}

void    Model::mouseMove(Uint8, InputManager*) {

}