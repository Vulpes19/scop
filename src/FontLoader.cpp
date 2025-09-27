#include "FontLoader.hpp"

FontLoader *FontLoader::instance = nullptr;

FontLoader::FontLoader(void) {
    if (TTF_Init() == -1) {
        throw(ErrorHandler("Error failed to init SDL_TTF: " + std::string(TTF_GetError()), __FILE__, __LINE__));
    }
    readFontDir();
}

FontLoader::~FontLoader(void) {
    // TTF_CloseFont(font);
    TTF_Quit();
}

void FontLoader::readFontDir(void) {
    DIR *directory = opendir("./assets/fonts");
    struct dirent *dir;

    if (directory == NULL) {
        throw(ErrorHandler("Error opening directory /assets/textures to load textures", __FILE__, __LINE__));
    }
    while ((dir = readdir(directory)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            std::string fullPath = "/assets/fonts/" + std::string(dir->d_name);
            loadFont(fullPath.c_str());
        }
    }
    (void)closedir(directory);
}

FontLoader* FontLoader::getInstance(void)
{
	if (instance == nullptr)
		instance = new FontLoader();
	return (instance);
}

void    FontLoader::loadFont(const char *path) {
    TTF_Font* font = TTF_OpenFont(path, 18);
    if (!font) {
        throw(ErrorHandler("Error failed to load font in path (" + std::string(path) + "): " + std::string(TTF_GetError()), __FILE__, __LINE__));
    }

    std::string strPath = std::string(path);
    std::string ID = strPath.substr(14);
    ID.erase(ID.find(".ttf"));

    fonts[ID] = font;
}

unsigned int FontLoader::nextPowerOfTwo(unsigned int n) {
    if (n == 0) 
        return 1;
    
    unsigned int p = 1;
    while (p < n) {
        p <<= 1; //p = p * 2
    }
    return p;
}

unsigned int    FontLoader::getText(std::string ID, const char *text) {
    auto it = fonts.find(ID);

    if (it != fonts.end()) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        SDL_Color color = {255, 255, 255, 0};
        SDL_Surface* surface = TTF_RenderText_Blended(fonts[ID], text, color);

        int w = nextPowerOfTwo(surface->w);
        int h = nextPowerOfTwo(surface->h);
        
        SDL_Surface *intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

        SDL_Rect destRect;
        destRect.x = (w - surface->w) / 2;  // Center horizontally
        destRect.y = (h - surface->h) / 2;  // Center vertically
        destRect.w = surface->w;
        destRect.h = surface->h;

        SDL_BlitSurface(surface, 0, intermediary, &destRect);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, intermediary->pixels);
    
        SDL_FreeSurface(surface);
	    SDL_FreeSurface(intermediary);
        
        return (texture);
    }

    return UINT_MAX;
}