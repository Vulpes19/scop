#include "Label.hpp"

Label::Label(void)
{}

Label::~Label(void)
{}

void	Label::addButtonType(std::string ID, int w, int h, SDL_Color color, SDL_Color hoverColor)
{
	Button *button = new Button(h, w, color, hoverColor);
	labels[ID] = button;
}

void	Label::deleteButtonType(std::string ID)
{
	auto it = labels.find(ID);
	if (it != labels.end())
	{
		delete it->second;
		labels.erase(ID);
	}
	std::cout << "THIS WAS DELETED" << std::endl;
}

void	Label::render(int x, int y, int textSize, std::string ID, std::string content, SDL_Color textColor, std::string font, SDL_Renderer* renderer, BUTTON_STATE state)
{
    (void)state;
	auto label = labels.find(ID);
	if (label == labels.end())
		throw(ErrorHandler("Can't find label with ID: " + ID, __FILE__, __LINE__));
	//coloring the button label
	SDL_Rect rect = { x, y, label->second->width, label->second->height };
    if (state == HOVER_OFF)
        SDL_SetRenderDrawColor(renderer,
            label->second->color.r,
            label->second->color.g,
            label->second->color.b,
            label->second->color.a);
    else
        SDL_SetRenderDrawColor(renderer,
            label->second->hoverColor.r,
            label->second->hoverColor.g,
            label->second->hoverColor.b,
            label->second->hoverColor.a);  
	//drawing the button rect
	SDL_RenderFillRect(renderer, &rect);
    //getting the font
	SDL_Surface* textSurface = FontLoader::getInstance()->getFont(font, content.c_str(), textColor);
	if (textSurface == NULL)
		throw(ErrorHandler("Error rendering text: " + std::string(TTF_GetError()), __FILE__, __LINE__));
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture == NULL)
		throw(ErrorHandler("Error creating text texture from surface: " + std::string(TTF_GetError()), __FILE__, __LINE__));
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
	SDL_FreeSurface(textSurface);

    //getting text position in the middle of UI label
	int midX = x + (labels[ID]->width - textWidth * textSize) / 2;
    int midY = y + (labels[ID]->height - textHeight * textSize) / 2;
	SDL_Rect textRect = { midX, midY, textWidth * textSize, textHeight * textSize };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
}