#pragma once

#include <iostream>

class Vector {
    public :
        //constructors
        Vector(void);
        Vector(double x, double y, double z = 0);
        Vector(const Vector &vec);

        ~Vector(void);
        // vector operations
        Vector  operator+(double scalar);
        Vector  operator-(double scalar);
        Vector  operator*(double scalar);
        Vector  operator/(double scalar);
        Vector  &operator*=(double scalar);
        Vector  &operator+=(double scalar);
        Vector  &operator-=(double scalar);
        Vector  &operator/=(double scalar);
        
        double  length(void);
        void    normalize(void);

        double x;
        double y;
        double z;
        double w = 1;
};