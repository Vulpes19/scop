#pragma once

#include "SDL_image.h"
#include <iostream>
#include <map>
#include "ErrorHandler.hpp"

class TextureLoader {
    public:
        ~TextureLoader(void);
        static TextureLoader* getInstance(void);
        void loadImage(const char *);
        SDL_Surface *getImage(std::string);
    private:
        static TextureLoader* instance;
        TextureLoader(void);
        std::map<std::string, SDL_Surface *> textures;
};