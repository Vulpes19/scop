#include <iostream>
#include <SDL2/SDL.h>
#include "App.hpp"

int main (int ac, char **av) {
    try {
        App *app = new App();
        while (app->isRunning())
        {
            app->handleInput();
            app->update();
            app->render();
        }
        delete app;
    }
    catch (const ErrorHandler &e)
	{
		std::cerr << e.what() << " - " << "in file: " << e.getFile() << " line: " << e.getLine() << std::endl;
	}
    return (0);
}
