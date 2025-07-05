#include "Camera.hpp"
#include "InputManager.hpp"

Camera::Camera(Vector position, Vector front, Vector up) {
    cameraPosition = position;
    cameraFront = front;
    cameraUp = up;

    view.identity();
}

Camera::~Camera(void) {

}

Vulpes3D::Matrix4x4   Camera::getView(void) {
    view.identity();
    return (view.lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp));
}

void    Camera::keyDown(SDL_Scancode key, float deltaTime, InputManager*, Camera* ) {
    float velocity = movementSpeed * deltaTime;

    if (InputDetector::getInstance()->isKeyPressed(key)) {
        if (key == SDL_SCANCODE_W)
            cameraPosition += cameraFront * velocity;
        if (key == SDL_SCANCODE_S)
            cameraPosition -= cameraFront * velocity;
        if (key == SDL_SCANCODE_A)
            cameraPosition -= cameraFront.crossProduct(cameraUp).normalize() * velocity;
        if (key == SDL_SCANCODE_D)
            cameraPosition += cameraFront.crossProduct(cameraUp).normalize() * velocity;
    }
}

void    Camera::mouseMove(Uint8, InputManager* ) {

}