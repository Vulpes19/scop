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
    TTF_Font* font = TTF_OpenFont(path, 24);
    if (!font) {
        throw(ErrorHandler("Error failed to load font in path (" + std::string(path) + "): " + std::string(TTF_GetError()), __FILE__, __LINE__));
    }

    std::string strPath = std::string(path);
    std::string ID = strPath.substr(14);
    ID.erase(ID.find(".ttf"));

    fonts[ID] = font;
}

SDL_Surface *FontLoader::getFont(std::string ID, const char *text) {
    auto it = fonts.find(ID);

    if (it != fonts.end()) {
        SDL_Color color = {255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Blended(fonts[ID], text, color);
        if (surface == NULL)
            throw(ErrorHandler("Error loading text from font <" + ID + ">" + std::string(TTF_GetError()), __FILE__, __LINE__));
        return (surface);
    }

    return NULL;
}