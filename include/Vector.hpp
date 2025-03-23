#pragma once

#include <iostream>

class Vector {
    public :
        //constructors
        Vector(void);
        Vector(float x, float y, float z = 0.0f);
        Vector(const Vector &vec);

        ~Vector(void);
        // vector operations
        Vector  operator+(float scalar);
        Vector  operator-(float scalar);
        Vector  operator*(float scalar);
        Vector  operator/(float scalar);
        Vector  &operator*=(float scalar);
        Vector  &operator+=(float scalar);
        Vector  &operator-=(float scalar);
        Vector  &operator/=(float scalar);
        
        float  crossProduct(const Vector &vec);
        float  dotProduct(const Vector &vec);
        float  length(void);
        void    normalize(void);

        float x;
        float y;
        float z;
        float w = 1.0f;
};