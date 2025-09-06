#include "MainMenu.hpp"

MainMenu::MainMenu(void)
{
	stateName = MainMenuState;

	label.addButtonType("MainMenu", 200, 80, { 242, 213, 248, 255 }, { 255, 255, 255, 255 });

	buttonsState["Start"] = HOVER_ON;
	buttonsState["Quit"] = HOVER_OFF;
}

MainMenu::~MainMenu(void)
{
}

void	MainMenu::keyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera*, SDL_Renderer*)
{
	(void)deltaTime;
	if (InputDetector::getInstance()->isKeyPressed(key) && StatesManager::getInstance()->getCurrentState() == MainMenuState)
	{
		if (key == SDL_SCANCODE_UP)
		{
			buttonsState["Start"] = HOVER_ON;
			buttonsState["Quit"] = HOVER_OFF;
		}
		if (key == SDL_SCANCODE_DOWN)
		{
			buttonsState["Start"] = HOVER_OFF;
			buttonsState["Quit"] = HOVER_ON;
		}
		if (key == SDL_SCANCODE_RETURN && buttonsState["Start"] == HOVER_ON)
		{
			std::cout << "entering 1" << std::endl;
			StatesManager::getInstance()->addState(new ListScenesMenu());
			InputObserver* scenesObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
			if (scenesObserver)
				input->addObserver(scenesObserver);
			else
				throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__));
		}
		if (key == SDL_SCANCODE_RETURN && buttonsState["Quit"] == HOVER_ON) {
			StatesManager::getInstance()->removeState(input);
			return ;
		}
	}
}


void	MainMenu::handleInput(void)
{

}

void	MainMenu::update(float)
{

}

void	MainMenu::render(Vulpes3D::Matrix4x4, SDL_Renderer *renderer)
{
	// SDL_RenderClear(renderer);

	// label.render(
	// 	(WIDTH - 200) / 2, // X pos
	// 	300,    		   // Y pos
	// 	2,                 // Text size
	// 	"MainMenu",        // Button type
	// 	"Start",           // Button text
	// 	{2, 52, 54, 255},  // text color
	// 	"Prisma",          // font name
	// 	renderer, 
	// 	buttonsState["Start"]); // State of button (Hover_on or Hover_off)
	// label.render((WIDTH - 200) / 2, 400, 2, "MainMenu", "Quit", {2, 52, 54, 255}, "Prisma", renderer, buttonsState["Quit"]);

	// SDL_SetRenderDrawColor(renderer, 2, 52, 54, 255);
}