#pragma once

#include <SDL.h>
#include "InputManager.hpp"
// #include "Camera.hpp"

class InputManager;
class Camera;

class InputObserver
{
	public:
		virtual void	keyDown(SDL_Scancode, float, InputManager* = nullptr, Camera* = nullptr) = 0;
		virtual void	mouseMove(Uint8, InputManager* = nullptr) = 0;
};