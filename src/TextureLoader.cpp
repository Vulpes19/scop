#include "TextureLoader.hpp"

TextureLoader *TextureLoader::instance = nullptr;

TextureLoader::TextureLoader(void) {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw(ErrorHandler("Error failed to init SDL_image: " + std::string(IMG_GetError()), __FILE__, __LINE__));
    }
    readTextureDir();
}

TextureLoader::~TextureLoader(void) {
    
}

void TextureLoader::readTextureDir(void) {
    DIR *directory = opendir("./assets/textures");
    struct dirent *dir;

    if (directory == NULL) {
        throw(ErrorHandler("Error opening directory /assets/textures to load textures", __FILE__, __LINE__));
    }
    while ((dir = readdir(directory)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            std::string fullPath = "/assets/textures/" + std::string(dir->d_name);
            std::cout << fullPath << std::endl;
            loadImage(fullPath.c_str());
        }
    }
    (void)closedir(directory);
}

TextureLoader* TextureLoader::getInstance(void)
{
	if (instance == nullptr)
		instance = new TextureLoader();
	return (instance);
}

void    TextureLoader::loadImage(const char *path) {
    SDL_Surface* image = IMG_Load(path);
    if (!image) {
        throw(ErrorHandler("Error failed to load image in path (" + std::string(path) + "): " + std::string(IMG_GetError()), __FILE__, __LINE__));
    }

    std::string strPath = std::string(path);
    size_t index = strPath.find("assets");

    if (index == std::string::npos)
        throw(ErrorHandler("Error failed to load image: can't name the texture the path should have 'assets'", __FILE__, __LINE__));   
    
    textures.push_back(image);
}

SDL_Surface *TextureLoader::getImage(size_t &index) {
    index += 1;
    if (textures.empty())
        return NULL;
    if (index == textures.size()) {
        index = 0;
    }
    return textures[index];
}