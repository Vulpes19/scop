#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Shader.hpp"
#include "SDL.h"
#include "TextureLoader.hpp"
#include "Matrix.hpp"
#include <vector>
#include "InputObserver.hpp"
#include "InputDetector.hpp"
#include <sstream>
#include <algorithm>


struct VertexIndex {
    VertexIndex(void) {};
    VertexIndex(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {};
    int v, vt, vn;
};

struct Face {
    VertexIndex v1, v2, v3;
};

struct Vertex {
    Vector position;
    Vector normal;
    Vector2 texCoord;
};

struct Mesh {
    std::vector<Vector> vertices;
    std::vector<Vector2> textureCoord;
    std::vector<Vector> normals;
    std::vector<Face> faces;
};

struct Material {
    std::string name;
    bool        isMaterial = false;
    float Ns;
    Vector  Ka;
    Vector  Kd;
    Vector  Ks;
    float   Ni;
    float   d;
    int     illum;
};

class Model : public InputObserver {
    public:
        Model(std::string);
        ~Model(void);
        void    parseModel(std::string&);
        std::vector<VertexIndex>    parseFaceVertex(std::string&);
        void    parseMaterial(void);
        void    render(Vulpes3D::Matrix4x4 view);
        void    update(void);
        void	keyDown(SDL_Scancode, float, InputManager * = nullptr) override;
        void	mouseMove(Uint8, InputManager* = nullptr) override;
    private:
        struct Mesh mesh;
        struct Material material;
        std::vector<Vertex> vertexBuffer;
        unsigned int VBO; //vertex buffer object we need to store verticies in GPU memory
        unsigned int VAO;
        unsigned int EBO;
        Shader      *shader;
        unsigned int texture1;
        unsigned int texture2;
        Vulpes3D::Matrix4x4   model;;
        Vulpes3D::Matrix4x4   projection;
        unsigned int          modelLoc;
        unsigned int          projectionLoc;
        unsigned int          viewLoc;
        float                 angle = 0.0f;
        Vector                center;
};