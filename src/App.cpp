#include "App.hpp"

App::App(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw(ErrorHandler("SDL failed to initialise: " + std::string(SDL_GetError()), __FILE__, __LINE__));
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("scop",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL)
		throw(ErrorHandler("SDL window failed to initialise: " + std::string(SDL_GetError()), __FILE__, __LINE__));

	context = SDL_GL_CreateContext(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			throw(ErrorHandler("GLAD failed to initialise: " + std::string(SDL_GetError()), __FILE__, __LINE__));
    }
    glViewport( 0, 0, WIDTH, HEIGHT );

	triangle = new Object();
	//init App stuff
	running = true;
}

App::~App(void) {
	SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void    App::handleInput(void) {
    while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

void    App::update(void) {
}

void    App::render(void) {
	triangle->render();
	SDL_GL_SwapWindow(window);
}

bool    App::isRunning(void) const {
    return (running);
}