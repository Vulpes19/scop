#pragma once

#include <SDL.h>
#include "InputManager.hpp"
// #include "Camera.hpp"

class InputManager;
class Camera;

class InputObserver
{
	public:
		virtual void	keyDown(SDL_Scancode, float, InputManager* = nullptr, Camera* = nullptr, SDL_Renderer* = nullptr) = 0;
};