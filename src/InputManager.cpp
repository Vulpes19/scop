#include "InputManager.hpp"

InputManager::InputManager(void)
{}

InputManager::~InputManager(void)
{}

void	InputManager::addObserver(InputObserver* newObserver)
{
	observers.push_back(newObserver);
}

void	InputManager::eraseObserver(InputObserver* observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);
	observers.erase(it);
}

void	InputManager::notifyOnKeyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera *camera, SDL_Renderer *renderer)
{
	for (auto observer : observers)
	{
		if (observer)
			observer->keyDown(key, deltaTime, input, camera, renderer);
	}
}
