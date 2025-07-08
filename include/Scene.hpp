#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Shader.hpp"
#include "SDL.h"
#include "TextureLoader.hpp"
#include "Matrix.hpp"
#include <vector>
#include "Camera.hpp"
#include "InputDetector.hpp"
#include <sstream>
#include <algorithm>
#include <string>
#include "State.hpp"
#include "StatesManager.hpp"


struct VertexIndex {
    VertexIndex(void) {};
    VertexIndex(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {};
    int v, vt, vn;
    bool isText = false;
    bool isNormal = false;
};

struct Face {
    VertexIndex v1, v2, v3;
};

struct Vertex {
    Vector  position;
    Vector  normal;
    Vector2 texCoord;
    Vector  color;
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
    float   Ns; // Shininess
    Vector  Ka; // Ambient color
    Vector  Kd; // Diffuse color
    Vector  Ks; // Specular color
    float   Ni; // Optical density (IOR)
    float   d;  // Transparency
    int     illum; // Illumination model
};

class Scene : public State, public InputObserver {
    public:
        Scene(std::string, Vector);
        ~Scene(void);
        void    parseModel(std::string&);
        std::vector<VertexIndex>    parseFaceVertex(std::string);
        void    parseMaterial(void);
		void    handleInput(void) override;
        void    render(Vulpes3D::Matrix4x4 view) override;
        void    update(float deltaTime) override;
        void	keyDown(SDL_Scancode, float, InputManager*, Camera* = nullptr) override;
    private:
        struct Mesh mesh;
        struct Material material;
        std::vector<Vertex> vertexBuffer;
        std::vector<Vector> colors;
        unsigned int VBO; //vertex buffer object we need to store verticies in GPU memory
        unsigned int VAO;
        unsigned int EBO;
        Vulpes3D::Matrix4x4   model;;
        Vulpes3D::Matrix4x4   projection;
        unsigned int          modelLoc;
        unsigned int          projectionLoc;
        unsigned int          viewLoc;
        unsigned int          texture1;
        size_t                textureIndex = -1;
        bool                  textureToggle = false;
        float                 blend = 0.0f;
        size_t                colorIndex = 0;
        float                 angle = 0.0f;
        Vector                center;
        int                   normalColoring = 0;
};