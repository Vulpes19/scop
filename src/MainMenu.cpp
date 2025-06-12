#include "MainMenu.hpp"

MainMenu::MainMenu(void)
{
	stateName = MainMenuState;
    #ifdef _WIN32
        shader = new Shader("C:\\Users\\asus\\Documents\\scop\\shaders\\MenuVertexShader.glsl", "C:\\Users\\asus\\Documents\\scop\\shaders\\MenuFragmentShader.glsl");
    #elif __APPLE__
        shader = new Shader("./shaders/MenuVertexShader.glsl", "./shaders/MenuFragmentShader.glsl");
    #elif __linux__
        shader = new Shader("./shaders/MenuVertexShader.glsl", "./shaders/MenuFragmentShader.glsl");
	// label.addButtonType("MainMenu", 80, 200, { 136, 8, 8, 255 });
	// buttonsState["Play"] = FOCUS_ON;
	// buttonsState["Quit"] = FOCUS_OFF;

    shader->compileShader(GL_VERTEX_SHADER);
    shader->compileShader(GL_FRAGMENT_SHADER);
    shader->createShader();

     glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
}

MainMenu::~MainMenu(void)
{}

void	MainMenu::keyDown(SDL_Scancode key, float deltaTime)
{
	// if (InputDetector::getInstance()->isKeyPressed(key) && StatesManager::getInstance()->getCurrentState() == MainMenuState)
	// {
	// 	if (key == SDL_SCANCODE_DOWN)
	// 	{
	// 		buttonsState["Play"] = FOCUS_OFF;
	// 		buttonsState["Quit"] = FOCUS_ON;
	// 	}
	// 	if (key == SDL_SCANCODE_UP)
	// 	{
	// 		buttonsState["Play"] = FOCUS_ON;
	// 		buttonsState["Quit"] = FOCUS_OFF;
	// 	}
	// 	if (key == SDL_SCANCODE_RETURN && buttonsState["Play"] == FOCUS_ON)
	// 	{
	// 		std::cout << "level menu is pushed" << std::endl;
	// 		StatesManager::getInstance()->addState(new LevelMenu());
	// 		InputObserver* levelObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
	// 		if (levelObserver)
	// 			input->addObserver(levelObserver);
	// 		else
	// 			throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__));
	// 	}
	// 	if (key == SDL_SCANCODE_RETURN && buttonsState["Quit"] == FOCUS_ON)
	// 		StatesManager::getInstance()->removeState(input);
	// }
}

void	MainMenu::mouseMove(Uint8 mouseButton, InputManager* input)
{
	// int x, y;
	// SDL_GetMouseState(&x, &y);
	// if (x >= 540 && x <= 740 && y >= 300 && y <= 380 && StatesManager::getInstance()->getCurrentState() == MainMenuState)
	// {
	// 	buttonsState["Play"] = FOCUS_ON;
	// 	buttonsState["Quit"] = FOCUS_OFF;
	// 	if (mouseButton == SDL_BUTTON_LEFT)
	// 	{
	// 		std::cout << "level menu is pushed" << std::endl;
	// 		StatesManager::getInstance()->addState(new LevelMenu());
	// 		InputObserver* levelObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
	// 		if (levelObserver)
	// 			input->addObserver(levelObserver);
	// 		else
	// 			throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__));
	// 	}
	// }
	// if (x >= 540 && x <= 740 && y >= 400 && y <= 480)
	// {
	// 	buttonsState["Play"] = FOCUS_OFF;
	// 	buttonsState["Quit"] = FOCUS_ON;
	// 	if (mouseButton == SDL_BUTTON_LEFT)
	// 		StatesManager::getInstance()->removeState(input);
	// }
}

void	MainMenu::handleInput(void)
{

}

void	MainMenu::update(float)
{

}

void	MainMenu::render(Vulpes3D::Matrix4x4)
{
    std::cout << "currently Main Menu state" << std::endl;
	// label.render(540, 300, "MainMenu", "Play", "Bangers", renderer, buttonsState["Play"]);
	// label.render(540, 400, "MainMenu", "Quit", "Bangers", renderer, buttonsState["Quit"]);
}