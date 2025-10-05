#pragma once

#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <map>
#include "ErrorHandler.hpp"
#include "./glad/glad.h"
#ifdef __APPLE__
    #include <dirent.h>
#elif __linux__
    #include <dirent.h>
#elif _WIN32
    #include <windows.h>
#endif

class FontLoader {
    public:
        ~FontLoader(void);
        static FontLoader* getInstance(void);
        void readFontDir(void);
        void loadFont(const char *);
        unsigned int    nextPowerOfTwo(unsigned int);
        unsigned int    getText(std::string, const char *, SDL_Color);
    private:
        static FontLoader* instance;
        FontLoader(void);
        std::map<std::string, TTF_Font*> fonts;
};