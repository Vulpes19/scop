#include "Matrix.hpp"

Matrix4x4::Matrix4x4(void) {

}

Matrix4x4::~Matrix4x4(void) {
    
}

Matrix4x4    Matrix4x4::identity(void) {
    Matrix4x4 matrix;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            matrix.mat[row][col] = (col == row) ? 1.0f : 0.0f;
            std::cout << matrix.mat[row][col] << " ";
        }
        std::cout << std::endl;
    }
    return matrix;
}

Matrix4x4   &Matrix4x4::translate(Vector vec) {
    mat[0][3] += vec.x;
    mat[1][3] += vec.y;
    mat[2][3] += vec.z;
    // matrix.mat[3][3] = 1.0f;
    std::cout << "=================" << std::endl;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << mat[row][col] << " ";
        }
        std::cout << std::endl;
    }
    return *this;
}

Matrix4x4   &Matrix4x4::scale(Vector vec) {
    mat[0][0] *= vec.x;
    mat[1][1] *= vec.y;
    mat[2][2] *= vec.z;
    // matrix.mat[3][3] = 1.0f;

    std::cout << "=================" << std::endl;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            std::cout << mat[row][col] << " ";
        }
        std::cout << std::endl;
    }
    return *this;
}

float   *Matrix4x4::data(void) {
    return &mat[0][0];
}