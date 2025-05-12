#pragma once

#include <SDL.h>
#include "InputManager.hpp"

class InputManager;

class InputObserver
{
	public:
		virtual void	keyDown(SDL_Scancode, float, InputManager * = nullptr) = 0;
		virtual void	mouseMove(Uint8, InputManager* = nullptr) = 0;
};