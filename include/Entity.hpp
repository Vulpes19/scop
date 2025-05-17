#pragma once

#include "Vector.hpp"
#include <iostream>

class Entity {
    public:
        virtual ~Entity(void);
        virtual void update(float deltaTime) {};
        virtual void render(void) {};

        Vector position;
        Vector rotation;
};