#pragma once

#include "State.hpp"
#include "InputDetector.hpp"
#include "Matrix.hpp"
#include "TextureLoader.hpp"
#include "StatesManager.hpp"
#include "ListScenesMenu.hpp"
#include "FontLoader.hpp"

#define WIDTH 1280
#define HEIGHT 640

enum quadType {
	TITLE,
	BUTTONN
};
class MainMenu : public State, public InputObserver
{
	public:
		MainMenu(void);
		~MainMenu(void);
		void initVertexData(enum quadType);
		void handleInput(void) override;
		void keyDown(SDL_Scancode, float, InputManager*, Camera* = nullptr) override;
		void update(float = 0) override;
		void render(Vulpes3D::Matrix4x4 view) override;
	private:
        unsigned int          text1;
        unsigned int          text2;
		unsigned int		  titleVBO;
		unsigned int		  titleVAO;
};