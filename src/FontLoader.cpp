#include "FontLoader.hpp"

FontLoader *FontLoader::instance = nullptr;

FontLoader::FontLoader(void) {
    if (TTF_Init() == -1) {
        throw(ErrorHandler("Error failed to init SDL_TTF: " + std::string(TTF_GetError()), __FILE__, __LINE__));
    }
    readFontDir();
}

FontLoader::~FontLoader(void) {
    for (auto it = fonts.begin(); it != fonts.end(); ++it) {
        TTF_CloseFont(it->second);
    }
    TTF_Quit();
}

void FontLoader::readFontDir(void) {
    #ifdef __APPLE__
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
    #elif _WIN32
    std::string fontDir = "assets\\fonts\\";
    std::string searchPath = fontDir + "*";
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Error opening directory: assets/fonts");
    }

    do {
        const char* name = findData.cFileName;

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;

        std::string fullPath = "assets\\fonts\\" + std::string(name);
        std::cout << fullPath << std::endl;

        loadFont(fullPath.c_str());

    } while (FindNextFile(hFind, &findData) != 0);
    #endif
}

FontLoader* FontLoader::getInstance(void)
{
	if (instance == nullptr)
		instance = new FontLoader();
	return (instance);
}

void    FontLoader::loadFont(const char *path) {
    TTF_Font* font = TTF_OpenFont(path, 28);
    if (!font) {
        throw(ErrorHandler("Error failed to load font in path (" + std::string(path) + "): " + std::string(TTF_GetError()), __FILE__, __LINE__));
    }

    std::string strPath = std::string(path);
    #ifdef __APPLE__
    int size = 14;
    #elif _WIN32
    int size = 13;
    #endif
    std::string ID = strPath.substr(size);
    ID.erase(ID.find(".ttf"));
    std::cout << "ID " << ID << std::endl;

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

unsigned int    FontLoader::getText(std::string ID, const char *text, SDL_Color color) {
    auto it = fonts.find(ID);

    std::cout << "fonts size " << fonts.size() << std::endl;
    if (it != fonts.end()) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        SDL_Surface* surface = TTF_RenderText_Solid(fonts[ID], text, color);

        int w = nextPowerOfTwo(surface->w);
        int h = nextPowerOfTwo(surface->h);
        
        SDL_Surface *intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

        SDL_Rect destRect;
        destRect.x = (w - surface->w) / 2;  // Center horizontally
        destRect.y = (h - surface->h) / 2;  // Center vertically
        destRect.w = surface->w;
        destRect.h = surface->h;

        SDL_BlitSurface(surface, 0, intermediary, &destRect);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);
    
        SDL_FreeSurface(surface);
	    SDL_FreeSurface(intermediary);
        
        return (texture);
    }

    return UINT_MAX;
}