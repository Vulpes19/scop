#pragma once

#include "State.hpp"
#include "Camera.hpp"
#include "InputDetector.hpp"
#include "Matrix.hpp"
#include "TextureLoader.hpp"
#include "StatesManager.hpp"
#include "Scene.hpp"
#include "FontLoader.hpp"

#define WIDTH 1280
#define HEIGHT 640

class ListScenesMenu : public State, public InputObserver
{
	public:
		ListScenesMenu(void);
		~ListScenesMenu(void);
		void handleInput(void) override;
		void keyDown(SDL_Scancode, float, InputManager*, Camera* = nullptr) override;
		void update(float = 0) override;
		void render(Vulpes3D::Matrix4x4 view) override;
		void getModels(void);
	private:
		std::vector<std::string> modelPaths;
		std::map<std::string, unsigned int> buttonTexts;
};