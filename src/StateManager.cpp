#include "StatesManager.hpp"

StatesManager* StatesManager::instance = nullptr;

StatesManager* StatesManager::getInstance(void)
{
	if (instance == nullptr)
		instance = new StatesManager();
	return (instance);
}

StatesManager::StatesManager(void)
{}

StatesManager::~StatesManager(void)
{}

void	StatesManager::addState(State* state)
{
	std::cout << "adding state: " << state->getStateName() << std::endl;
	std::cout << "states size: " << states.size() << std::endl;
	states.push_back(state);
	std::cout << "after adding states size: " << states.size() << std::endl;
}

void	StatesManager::removeState(InputManager *input)
{
	if (!states.empty())
	{
		std::cout << "states number " << states.size() << std::endl;
		InputObserver* observer = dynamic_cast<InputObserver*>(states.back());
		if (observer) {
			input->eraseObserver(observer);
		}
		delete states.back();
		states.pop_back();
	}
}

void	StatesManager::removeState(int n, InputManager *input)
{
	for (int i = 0; i < n; i++)
		removeState(input);
}

enum STATES	StatesManager::getCurrentState(void) const
{
	if (states.empty())
		return (NoState);
	else
		return (states.back()->getStateName());
}

State	*StatesManager::getCurrentStateInstance(void) const
{
	if (!states.empty())
		return (states.back());
	else
		return (NULL);
}

void	StatesManager::handleInput(void)
{
	if (!states.empty())
	{
		states.back()->handleInput();
	}
}

void	StatesManager::update(float deltaTime)
{
	if (!states.empty())
	{
		states.back()->update(deltaTime);
	}
}

void	StatesManager::render(void)
{
	if (!states.empty())
	{
		states.back()->render();
	}
}