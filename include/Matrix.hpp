#pragma once

#include <iostream>
#include "Vector.hpp"

class Matrix4x4 {
    public:
        Matrix4x4(void);
        ~Matrix4x4(void);

        static Matrix4x4 identity(void);
        Matrix4x4 &translate(Vector vec);
        Matrix4x4 &scale(Vector vec);
        // void rotate(Vector vec);

        float *data(void);

        float mat[4][4];
};