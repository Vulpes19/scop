#pragma once

#include "InputObserver.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Camera.hpp"

class InputObserver;
class Camera;

class InputManager
{
	public:
		InputManager(void);
		~InputManager(void);
		void	addObserver(InputObserver*);
		void	eraseObserver(InputObserver*);
		void	notifyOnKeyDown(SDL_Scancode, float, InputManager* = nullptr, Camera* = nullptr);
		void	notifyOnMouseMove(Uint8);
	private:
		std::vector<InputObserver*> observers;
};