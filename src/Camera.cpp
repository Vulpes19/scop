#include "Camera.hpp"

Camera::Camera(Vector position, Vector target, Vector up) {
    cameraPosition = position;
    target = cameraTarget;
    cameraUp = up;

    view.identity();
    // cameraPos = Vector(0.0f, 0.0f, 3.0f);
    // Vector cameraTarget = Vector(0.0f, 0.0f, 0.0f);

    // /* ******* Gram-Schmidt Process ******* */

    // // substracting the camera position from the scene's origin vector results
    // // in the direction vector we want.
    // // We switch the substraction because we want the Z axis to be positive because the
    // // camera points towards the negaive Z axis.
    // cameraDirection = cameraPos - cameraTarget;
    // // Actually it's reverse direction but it's because the camera points to the negative Z
    // cameraDirection.normalize();

    // Vector up = Vector(0.0f, 1.0f, 0.0f);
    // cameraRight = up.crossProduct(cameraDirection);
    // cameraRight.normalize();

    // cameraUp = cameraDirection.crossProduct(cameraRight);

    /* ******************************** */
}

Camera::~Camera(void) {

}

// Vulpes3D::Matrix4x4 &Camera::lookAt(Vector &target) {

// }

Vulpes3D::Matrix4x4   Camera::getView(void) {
    return (view.lookAt(cameraPosition, cameraTarget, cameraUp));
}

void    Camera::keyDown(SDL_Scancode key, float deltaTime, InputManager *input) {
    float velocity = movementSpeed * deltaTime;

    if (InputDetector::getInstance()->isKeyPressed(key)) {
        if (key == SDL_SCANCODE_W)
            cameraPosition += front * velocity;
        if (key == SDL_SCANCODE_S)
            cameraPosition -= front * velocity;
        if (key == SDL_SCANCODE_A)
            cameraPosition -= right * velocity;
        if (key == SDL_SCANCODE_D)
            cameraPosition += right * velocity;
    }
}

void    Camera::mouseMove(Uint8, InputManager* = nullptr) {

}