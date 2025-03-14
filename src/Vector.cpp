#include "Vector.hpp"

Vector::Vector(void) : x(0.0), y(0.0), z(0.0)
{}

Vector::Vector(double x, double y, double z = 0.0) : x(x), y(y), z(z)
{}

Vector::Vector(const Vector &vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector::~Vector(void)
{}

Vector    Vector::operator+(double scalar) {
    return (Vector(x + scalar, y + scalar, z + scalar));
}
Vector    Vector::operator-(double scalar) {
    return (Vector(x - scalar, y - scalar, z - scalar));
}
Vector    Vector::operator*(double scalar) {
    return (Vector(x * scalar, y * scalar, z * scalar));
}
Vector    Vector::operator/(double scalar) {
    return (Vector(x / scalar, y / scalar, z / scalar));
}
Vector  &Vector::operator*=(double scalar) {
    return (Vector(x * scalar, y * scalar, z * scalar));
}

double Vector::length(void) {
    return (sqrt(x * x + y * y + z * z));
}

void    Vector::normalize(void) {
    double length = this->length();

    if (length > 1)
        *this *= 1 / length;
}