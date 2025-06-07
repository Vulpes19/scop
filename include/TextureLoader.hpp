#pragma once

#include "SDL_image.h"
#include <iostream>
#include <map>
#include "ErrorHandler.hpp"
#ifdef __APPLE__
    #include <dirent.h>
#elif __linux__
    #include <dirent.h>
#elif _WIN32
    #include <windows.h>
#endif

class TextureLoader {
    public:
        ~TextureLoader(void);
        static TextureLoader* getInstance(void);
        void readTextureDir(void);
        void loadImage(const char *);
        SDL_Surface *getImage(size_t &);
    private:
        static TextureLoader* instance;
        TextureLoader(void);
        std::vector<SDL_Surface*> textures;
};