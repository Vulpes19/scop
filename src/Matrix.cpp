#include "Matrix.hpp"

using namespace Vulpes3D;

Matrix4x4::Matrix4x4(void) {

}

Matrix4x4::~Matrix4x4(void) {
    
}

Matrix4x4    Matrix4x4::identity(void) {
    Matrix4x4 matrix;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            matrix.mat[row][col] = (col == row) ? 1.0f : 0.0f;
            // std::cout << matrix.mat[row][col] << " ";
        }
        // std::cout << std::endl;
    }
    return matrix;
}

Matrix4x4   &Matrix4x4::translate(Vector vec) {
    mat[0][3] += vec.x;
    mat[1][3] += vec.y;
    mat[2][3] += vec.z;
    // matrix.mat[3][3] = 1.0f;
    // std::cout << "=================" << std::endl;
    // std::cout << "TRANSLATION" << std::endl;
    // std::cout << "=================" << std::endl;
    // for (int row = 0; row < 4; row++) {
    //     for (int col = 0; col < 4; col++) {
    //         std::cout << mat[row][col] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
    return *this;
}

Matrix4x4   &Matrix4x4::scale(Vector vec) {
    mat[0][0] *= vec.x;
    mat[1][1] *= vec.y;
    mat[2][2] *= vec.z;
    // matrix.mat[3][3] = 1.0f;

    // std::cout << "=================" << std::endl;
    // std::cout << "SCALING" << std::endl;
    // std::cout << "=================" << std::endl;
    // for (int row = 0; row < 4; row++) {
    //     for (int col = 0; col < 4; col++) {
    //         std::cout << mat[row][col] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return *this;
}

Matrix4x4   &Matrix4x4::rotate(Vector vec, enum AXIS axis, float angle) {
    //passed vector is not use until future implementation
    (void)vec;
    switch (axis)
    {
        case X_AXIS:
            mat[1][1] = cos(angle);
            mat[1][2] = -sin(angle);
            mat[2][1] = sin(angle);
            mat[2][2] = cos(angle);
            break;
        case Y_AXIS:
            mat[0][0] = cos(angle);
            mat[0][2] = sin(angle);
            mat[2][0] = -sin(angle);
            mat[2][2] = cos(angle);
            break;
        case Z_AXIS:
            mat[0][0] = cos(angle);
            mat[0][1] = -sin(angle);
            mat[1][0] = sin(angle);
            mat[1][1] = cos(angle);
            break;
        default:
            break;
    }
    // std::cout << "=================" << std::endl;
    // std::cout << "ROTATION" << std::endl;
    // std::cout << "=================" << std::endl;
    // for (int row = 0; row < 4; row++) {
    //     for (int col = 0; col < 4; col++) {
    //         std::cout << mat[row][col] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return *this;
}

Matrix4x4   &Matrix4x4::perspective(float fov, float aspect, float near_plane, float far_plane) {
    float tan_half_fov = tan(fov / 2.0f);

    mat[0][0] = 1.0f / (aspect * tan_half_fov);
    mat[1][1] = 1.0f / tan_half_fov;
    mat[2][2] = (far_plane + near_plane) / (near_plane - far_plane);   // <-- flipped
    mat[2][3] = -1.0f;
    mat[3][2] = (2.0f * far_plane * near_plane) / (near_plane - far_plane);  // <-- flipped
    mat[3][3] = 0.0f;

    // std::cout << "=================" << std::endl;
    // std::cout << "PROJECTION" << std::endl;
    // std::cout << "=================" << std::endl;
    // for (int row = 0; row < 4; row++) {
    //     for (int col = 0; col < 4; col++) {
    //         std::cout << mat[row][col] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return *this;
}

Matrix4x4& Matrix4x4::ortho(float left, float right, float bottom, float top, float near, float far) {

    mat[0][0] = 2.0f / (right - left);
    mat[1][1] = 2.0f / (top - bottom);
    mat[2][2] = -2.0f / (far - near);
    mat[3][0] = -(right + left) / (right - left);
    mat[3][1] = -(top + bottom) / (top - bottom);
    mat[3][2] = -(far + near) / (far - near);
    mat[3][3] = 1.0f;

    return *this;
}

Matrix4x4   &Matrix4x4::lookAt(Vector position, Vector target, Vector up) {
    Vector zAxis = (position - target).normalize();

    Vector xAxis = up.crossProduct(zAxis).normalize();

    Vector yAxis = zAxis.crossProduct(xAxis);
    
    //right vector
    mat[0][0] = xAxis.x;
    mat[0][1] = xAxis.y;
    mat[0][2] = xAxis.z;
    mat[0][3] = -xAxis.dotProduct(position);

    //up vector
    mat[1][0] = yAxis.x;
    mat[1][1] = yAxis.y;
    mat[1][2] = yAxis.z;
    mat[1][3] = -yAxis.dotProduct(position);

    //direction vector
    mat[2][0] = zAxis.x;
    mat[2][1] = zAxis.y;
    mat[2][2] = zAxis.z;
    mat[2][3] = -zAxis.dotProduct(position);

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
    return *this;
}

float   *Matrix4x4::data(void) {
    return &mat[0][0];
}

Matrix4x4   Matrix4x4::operator*(const Matrix4x4 &other) const {
    Matrix4x4   result;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.mat[row][col] = 
                mat[row][0] * other.mat[0][col] +
                mat[row][1] * other.mat[1][col] +
                mat[row][2] * other.mat[2][col] +
                mat[row][3] * other.mat[3][col];
        }
    }

    return (result);
}