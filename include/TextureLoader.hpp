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

enum Type {
    TEXTURE,
    BUTTON
};

class TextureLoader {
    public:
        ~TextureLoader(void);
        static TextureLoader* getInstance(void);
        void readTextureDir(const char *, enum Type type);
        void loadImage(const char *);
        void loadButtons(const char *);
        SDL_Surface *getImage(size_t &);
        SDL_Surface *getButton(std::string);
    private:
        static TextureLoader* instance;
        TextureLoader(void);
        std::vector<SDL_Surface*> textures;
        std::map<std::string, SDL_Surface*> buttons;
};