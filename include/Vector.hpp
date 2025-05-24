#pragma once

#include <iostream>

struct Vector2 {
    Vector2(void) : x(0.0f), y(0.0f) {};
    Vector2(float x, float y) : x(x), y(y) {};
    float x;
    float y;
};

class Vector {
    public :
        //constructors
        Vector(void);
        Vector(float x, float y, float z = 0.0f);
        Vector(const Vector &vec);

        ~Vector(void);
        // vector operations
        Vector  operator+(float scalar);
        Vector  operator+(const Vector &vec);
        Vector  operator-(float scalar);
        Vector  operator-(void);
        Vector  operator-(const Vector &vec);
        Vector  operator*(float scalar);
        Vector  operator/(float scalar);
        Vector  &operator*=(float scalar);
        Vector  &operator+=(float scalar);
        Vector  &operator+=(const Vector &vec);
        Vector  &operator-=(float scalar);
        Vector  &operator-=(const Vector &vec);
        Vector  &operator/=(float scalar);

        // friend std::ostream &operator<<(std::ostream& os, const Vector &vec);
        
        Vector  crossProduct(const Vector &vec);
        float   dotProduct(const Vector &vec);
        float   length(void);
        // void    normalize(void);
        Vector  normalize(void);

        float x;
        float y;
        float z;
        float w = 1.0f;
};

// std::ostream &operator<<(std::ostream& os, const Vector &vec) {
//     os << "(x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ")" << std::endl;
//     return os;
// }