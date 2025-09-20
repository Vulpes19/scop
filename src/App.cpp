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
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
		throw(ErrorHandler("SDL renderer failed to initialise: " + std::string(SDL_GetError()), __FILE__, __LINE__));
    glViewport( 0, 0, WIDTH, HEIGHT );

	camera = new Camera(Vector(0.0f, 0.0f, 3.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f));

	// model = new Model("42", camera->getPosition());
	input = new InputManager();
	State *mainMenu = new MainMenu();
	StatesManager::getInstance()->addState(mainMenu);

	InputObserver* cameraObserver = dynamic_cast<InputObserver*>(camera);
	InputObserver* stateObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
	// InputObserver* modelObserver = dynamic_cast<InputObserver*>(model);
	if (cameraObserver)
		 input->addObserver(cameraObserver);
	 else
		 throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__)); 
	if (stateObserver)
		 input->addObserver(stateObserver);
	 else
		 throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__)); 
	
	running = true;
}

App::~App(void) {
	SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
	// delete camera;
	delete input;
    SDL_Quit();
}

void    App::handleInput(void) {
    while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				input->notifyOnKeyDown(event.key.keysym.scancode, deltaTime, input, camera, renderer);
				break;
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

void    App::update(void) {
	if (StatesManager::getInstance()->getCurrentState() == NoState)
	{
		running = false;
		return ;
	}
	float currentFrame =(float)SDL_GetTicks() / 1000.0f; // SDL_GetTicks() returns milliseconds, so divide by 1000 to get seconds

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
	StatesManager::getInstance()->getCurrentStateInstance()->update(deltaTime);
}

void    App::render(void) {
	if (StatesManager::getInstance()->getCurrentState() != NoState) {
		StatesManager::getInstance()->getCurrentStateInstance()->render(camera->getView(), renderer);
		if (StatesManager::getInstance()->getCurrentState() == MainMenuState ||
			StatesManager::getInstance()->getCurrentState() == ListScenesMenuState)
			SDL_RenderPresent(renderer);
		else {
			if (renderer) {
				std::cout << "hello, renderer destroyed" << std::endl;
				SDL_DestroyRenderer(renderer);
				renderer = nullptr;
				SDL_GL_MakeCurrent(window, context);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
			// std::cout << "swapping windows" << std::endl;
			SDL_GL_SwapWindow(window);
		}
	}
}

bool    App::isRunning(void) const {
    return (running);
}