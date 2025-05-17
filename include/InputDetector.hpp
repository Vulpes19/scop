#pragma once

#include <SDL.h>
#include "Vector.hpp"

class InputDetector
{
	public:
		~InputDetector(void);
		static InputDetector* getInstance(void);
		bool	isKeyPressed(SDL_Scancode) const;
	private:
		InputDetector(void);
		static InputDetector* instance;
		const Uint8* keyboardState = SDL_GetKeyboardState(0);
};