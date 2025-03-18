#pragma once

#include <iostream>
#include "Vector.hpp"
#include <cmath>

enum AXIS {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

class Matrix4x4 {
    public:
        Matrix4x4(void);
        ~Matrix4x4(void);

        static Matrix4x4 identity(void);
        Matrix4x4 &translate(Vector vec);
        Matrix4x4 &scale(Vector vec);
        Matrix4x4 &rotate(Vector vec, enum AXIS, float angle);

        float *data(void);

        float mat[4][4];
    private:
        static const float PI;
};