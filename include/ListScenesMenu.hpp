#pragma once

#include "State.hpp"
#include "InputObserver.hpp"
#include "InputDetector.hpp"
#include "Matrix.hpp"
#include "TextureLoader.hpp"
#include "StatesManager.hpp"

#define WIDTH 1280
#define HEIGHT 640

class ListScenesMenu : public State, public InputObserver
{
	public:
		ListScenesMenu(void);
		~ListScenesMenu(void);
		void handleInput(void) override;
		void keyDown(SDL_Scancode, float, InputManager*) override;
		void mouseMove(Uint8, InputManager* = nullptr) override;
		void update(float = 0) override;
		void render(Vulpes3D::Matrix4x4 view) override;
};