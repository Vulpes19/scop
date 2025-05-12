#pragma once

#include "InputObserver.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

class InputObserver;

class InputManager
{
	public:
		InputManager(void);
		~InputManager(void);
		void	addObserver(InputObserver*);
		void	eraseObserver(InputObserver*);
		void	notifyOnKeyDown(SDL_Scancode, double);
		void	notifyOnMouseMove(Uint8);
	private:
		std::vector<InputObserver*> observers;
};