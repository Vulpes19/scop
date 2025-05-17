#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Matrix.hpp"
#include "InputObserver.hpp"
#include "InputDetector.hpp"

class Camera : public InputObserver {
    public:
        Camera(Vector position, Vector target, Vector up);
        ~Camera(void);
        Vulpes3D::Matrix4x4 getView(void);
        void	keyDown(SDL_Scancode, float, InputManager * = nullptr) override;
        void	mouseMove(Uint8, InputManager* = nullptr) override;
    private:
        Vector cameraPosition; 
        Vector cameraTarget;
        Vector cameraFront;
        Vector cameraRight;
        Vector cameraUp;
        Vector right;
        Vulpes3D::Matrix4x4 view;
        float   movementSpeed = 10.5f;
        float   movementSensitivity;
        float   zoom;
};