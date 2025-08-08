#pragma once

#include <iostream>
#include "ErrorHandler.hpp"
#include <SDL.h>
#include "Object.hpp"
#include "./glad/glad.h"
#include "Scene.hpp"
#include "StatesManager.hpp"
#include "MainMenu.hpp"

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
        SDL_GLContext context = nullptr;
		SDL_Event	event;
        Camera  *camera;
        InputManager    *input;
        float   deltaTime = 0.0f;
        float   lastFrame = 0.0f;
		bool	running = false;
};