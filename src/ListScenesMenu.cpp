#include "ListScenesMenu.hpp"

ListScenesMenu::ListScenesMenu(void)
{
    std::cout << "im rendering now menu" << std::endl;
	stateName = ListScenesMenuState;

	getModels();
	label.addButtonType("ScenesMenu", 250, 150, { 242, 213, 248, 255 }, { 255, 255, 255, 255 });

	selectedIndex = 0;
	for (int i = 0; i < modelPaths.size(); i++) {
        buttonsState[i] = (i == 0) ? HOVER_ON : HOVER_OFF;
    }
}

ListScenesMenu::~ListScenesMenu(void)
{}

void	ListScenesMenu::keyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera *camera, SDL_Renderer *renderer)
{
	(void)deltaTime;
	if (InputDetector::getInstance()->isKeyPressed(key) && StatesManager::getInstance()->getCurrentState() == ListScenesMenuState)
	{
		if (key == SDL_SCANCODE_RIGHT)
		{
			buttonsState[selectedIndex] = HOVER_OFF;
			auto it = buttonsState.find(selectedIndex + 1);
			if (it != buttonsState.end())
				selectedIndex += 1;
			else {
				selectedIndex = 0;
			}
			buttonsState[selectedIndex] = HOVER_ON;
		}
		if (key == SDL_SCANCODE_LEFT)
		{
			buttonsState[selectedIndex] = HOVER_OFF;
			auto it = buttonsState.find(selectedIndex - 1);
			if (it != buttonsState.end())
				selectedIndex -= 1;
			else {
				selectedIndex = modelPaths.size() - 1;
			}
			buttonsState[selectedIndex] = HOVER_ON;
		}
		if (key == SDL_SCANCODE_RETURN)
		{
			std::cout << "ENTER " << selectedIndex << std::endl;
			std::string strPath = modelPaths[selectedIndex];
			std::string ID = strPath.substr(16);
			ID.erase(ID.find(".obj"));
			std::cout << "loading: " << ID << std::endl;
			std::cout << "entering 2" << std::endl;
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
			StatesManager::getInstance()->addState(new Scene(ID, camera->getPosition()));
			InputObserver* levelObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
			if (levelObserver)
				input->addObserver(levelObserver);
			else
				throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__));
		}
		if (key == SDL_SCANCODE_ESCAPE) {
			StatesManager::getInstance()->removeState(input);
			return ;
		}
	}
}


void	ListScenesMenu::handleInput(void)
{

}

void	ListScenesMenu::update(float)
{

}

void	ListScenesMenu::render(Vulpes3D::Matrix4x4, SDL_Renderer *renderer)
{
	SDL_RenderClear(renderer);

	int modelIndex = 0;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 3; ++i) {
			float yPadding = (j == 0) ? 50.0f : 400.0f;
			std::string modelName = modelPaths[modelIndex].substr(16);
    		modelName.erase(modelName.find(".obj"));
			// std::cout << modelName << std::endl;
			label.render(
				i * 500,           // X pos
				yPadding,    	   // Y pos
				2,                 // Text size
				"ScenesMenu",      // Button type
				modelName,         // Button text
				{2, 52, 54, 255},  // text color
				"Prisma",          // font name
				renderer, 
				buttonsState[modelIndex]); // State of button (Hover_on or Hover_off)
			modelIndex += 1;
			if (modelPaths.size() - 1 < (size_t)modelIndex || 5 < (size_t)modelIndex)
				break;
		}
	}
	SDL_SetRenderDrawColor(renderer, 2, 52, 54, 255);
}

void ListScenesMenu::getModels(void) {
	DIR *directory = opendir("./assets/models/");
    struct dirent *dir;

    if (directory == NULL) {
        throw(ErrorHandler("Error opening directory /assets/models to load models", __FILE__, __LINE__));
    }
    while ((dir = readdir(directory)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            std::string fullPath = "./assets/models/" + std::string(dir->d_name);
            modelPaths.push_back(fullPath);
        }
    }
    (void)closedir(directory);
}