#pragma once

#include "./glad/glad.h"
#include <iostream>
#include "Matrix.hpp"
#include "InputObserver.hpp"
#include "InputDetector.hpp"
// #include "InputManager.hpp"

class InputManager;


class Camera : public InputObserver {
    public:
        Camera(Vector position, Vector target, Vector up);
        ~Camera(void);
        Vulpes3D::Matrix4x4 getView(void);
        void	keyDown(SDL_Scancode, float, InputManager*, Camera* = nullptr, SDL_Renderer* = nullptr) override;
        Vector  getPosition(void) const { return cameraPosition; };
    private:
        Vector cameraPosition; 
        Vector cameraTarget;
        Vector cameraFront;
        Vector cameraRight;
        Vector cameraUp;
        Vector right;
        Vulpes3D::Matrix4x4 view;
        float   movementSpeed = 20.0f;
        // float   movementSensitivity;
        // float   zoom;
};