#pragma once

#include "State.hpp"
#include "InputObserver.hpp"
#include "InputDetector.hpp"
#include "Matrix.hpp"

class MainMenu : public State, public InputObserver
{
	public:
		MainMenu(void);
		~MainMenu(void);
		void handleInput(void) override;
		void keyDown(SDL_Scancode, float) override;
		void mouseMove(Uint8, InputManager* = nullptr) override;
		void update(float = 0) override;
		void render(Vulpes3D::Matrix4x4 view) override;
	private:
		// std::map<std::string, BUTTON_STATE> buttonsState;
};