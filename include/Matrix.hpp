#pragma once

#include <iostream>
#include "Vector.hpp"
#include <cmath>

enum AXIS {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

namespace Vulpes3D {

    const float PI = 3.1415926535897f;

    float     to_radians(float angle);
    
    class Matrix4x4 {
        public:
            Matrix4x4(void);
            Matrix4x4(Vector A, Vector B, Vector C);
            ~Matrix4x4(void);

            static Matrix4x4 identity(void);

            //transformation matrices
            Matrix4x4   &translate(Vector vec);
            Matrix4x4   &scale(Vector vec);
            Matrix4x4   &rotate(Vector vec, enum AXIS, float angle);

            //perspective projection matrix
            Matrix4x4   &perspective(float fov, float aspect, float near_plane, float far_plane);

            // This matrix transforms all thr world coordinates to the view space
            Matrix4x4   &lookAt(Vector position, Vector direction, Vector up);

            // operations
            Matrix4x4  operator*(const Matrix4x4 &other) const;

            float *data(void);

            float mat[4][4];
    };

};