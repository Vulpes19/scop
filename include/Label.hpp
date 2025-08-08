#pragma once

#include "FontLoader.hpp"

enum BUTTON_STATE {
	HOVER_ON,
	HOVER_OFF
};

#define WIDTH 1280
#define TILE 20

struct Button {
	Button(int h, int w, SDL_Color color, SDL_Color hoverColor) : height(h), width(w), color(color), hoverColor(hoverColor) {};
	int height;
	int width;
	SDL_Color color;
	SDL_Color hoverColor;
};

class Label
{
	public:
		Label(void);
		~Label(void);
		void	addButtonType(std::string, int, int, SDL_Color, SDL_Color);
		void	deleteButtonType(std::string);
		void	render(int x, int y, int size,
			std::string ID, std::string content, SDL_Color textColor,
			std::string font, SDL_Renderer* renderer, BUTTON_STATE);
	private:
		std::map<std::string, Button *> labels;
};