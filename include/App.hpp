#pragma once

#include <iostream>
#include "ErrorHandler.hpp"
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

class App {
    public:
        App(void);
        ~App(void);
        void	handleInput(void);
        void	update(void);
        void	render(void);
        bool	isRunning(void) const;
    private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Event	event;
		bool	running = false;
};