#include "TextureLoader.hpp"

TextureLoader *TextureLoader::instance = nullptr;

TextureLoader::TextureLoader(void) {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw(ErrorHandler("Error failed to init SDL_image: " + std::string(IMG_GetError()), __FILE__, __LINE__));
    }
}

TextureLoader::~TextureLoader(void) {
    
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
        throw(ErrorHandler("Error failed to load image: " + std::string(IMG_GetError()), __FILE__, __LINE__));
    }

    std::string strPath = std::string(path);
    size_t index = strPath.find("assets");
    if (index == std::string::npos)
        throw(ErrorHandler("Error failed to load image: can't name the texture the path should have 'assets'", __FILE__, __LINE__));   
    
    std::string ID = strPath.substr(index + 7, strPath.length() - 40);

    textures[ID] = image;
}

SDL_Surface *TextureLoader::getImage(std::string ID) {
    auto image = textures.find(ID);

    if (image != textures.end())
        return (textures[ID]);
    else
        throw(ErrorHandler("Error failed to load image: unable to find image with the name: " + ID, __FILE__, __LINE__));
}