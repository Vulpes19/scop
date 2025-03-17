#include "Vector.hpp"

Vector::Vector(void) : x(0.0f), y(0.0f), z(0.0f)
{}

Vector::Vector(float x, float y, float z = 0.0f) : x(x), y(y), z(z)
{}

Vector::Vector(const Vector &vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector::~Vector(void)
{}

Vector    Vector::operator+(float scalar) {
    return (Vector(x + scalar, y + scalar, z + scalar));
}
Vector    Vector::operator-(float scalar) {
    return (Vector(x - scalar, y - scalar, z - scalar));
}
Vector    Vector::operator*(float scalar) {
    return (Vector(x * scalar, y * scalar, z * scalar));
}
Vector    Vector::operator/(float scalar) {
    return (Vector(x / scalar, y / scalar, z / scalar));
}
Vector  &Vector::operator*=(float scalar) {
    return (Vector(x * scalar, y * scalar, z * scalar));
}
Vector  &Vector::operator+=(float scalar) {
    return (Vector(x + scalar, y + scalar, z + scalar));
}
Vector  &Vector::operator-=(float scalar) {
    return (Vector(x - scalar, y - scalar, z - scalar));
}
Vector  &Vector::operator/=(float scalar) {
    return (Vector(x / scalar, y / scalar, z / scalar));
}

float Vector::length(void) {
    return (sqrt(x * x + y * y + z * z));
}

void    Vector::normalize(void) {
    float length = this->length();

    if (length > 1)
        *this *= 1 / length;
}