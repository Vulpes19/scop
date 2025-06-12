#pragma once

#include <iostream>
#include "ErrorHandler.hpp"
#include <SDL.h>
#include "Object.hpp"
#include "./glad/glad.h"
#include "Model.hpp"
#include "StatesManager.hpp"
#include "MainMenu.hpp"

#define WIDTH 1280
#define HEIGHT 640

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
        SDL_GLContext context = nullptr;
		SDL_Event	event;
        Model  *model;
        Camera  *camera;
        InputManager    *input;
        float   deltaTime = 0.0f;
        float   lastFrame = 0.0f;
		bool	running = false;
};