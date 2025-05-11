#include "Camera.hpp"

Camera::Camera(void) {
    cameraPos = Vector(0.0f, 0.0f, 3.0f);
    Vector cameraTarget = Vector(0.0f, 0.0f, 0.0f);

    /* ******* Gram-Schmidt Process ******* */

    // substracting the camera position from the scene's origin vector results
    // in the direction vector we want.
    // We switch the substraction because we want the Z axis to be positive because the
    // camera points towards the negaive Z axis.
    cameraDirection = cameraPos - cameraTarget;
    // Actually it's reverse direction but it's because the camera points to the negative Z
    cameraDirection.normalize();

    Vector up = Vector(0.0f, 1.0f, 0.0f);
    cameraRight = up.crossProduct(cameraDirection);
    cameraRight.normalize();

    cameraUp = cameraDirection.crossProduct(cameraRight);

    /* ******************************** */
}

Camera::~Camera(void) {

}

// Vulpes3D::Matrix4x4 &Camera::lookAt(Vector &target) {

// }

float   *Camera::getView(void) {
    return (view.data());
}