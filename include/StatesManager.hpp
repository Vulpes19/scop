#pragma once

#include "State.hpp"
#include <vector>
#include "InputManager.hpp"

class StatesManager
{
	public:
		~StatesManager(void);
		static StatesManager* getInstance(void);
		void	addState(State*);
		void	removeState(InputManager*);
		void	removeState(int, InputManager*);
		void	handleInput(void);
		void	update(float);
		void	render(void);
		enum STATES	getCurrentState(void) const;
		State* getCurrentStateInstance(void) const;
	private:
		StatesManager(void);
		static StatesManager *instance;
		std::vector<State*> states;
};