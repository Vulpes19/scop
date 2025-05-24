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

	camera = new Camera(Vector(0.0f, 0.0f, 3.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 1.0f, 0.0f));
	// triangle = new Object();
	model = new Model("42", camera->getPosition());
	// model = new Model("42");
	// model = new Model("teapot");
	input = new InputManager();

	InputObserver* cameraObserver = dynamic_cast<InputObserver*>(camera);
	InputObserver* modelObserver = dynamic_cast<InputObserver*>(model);
	if (cameraObserver)
		 input->addObserver(cameraObserver);
	 else
		 throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__)); 
	if (modelObserver)
		 input->addObserver(modelObserver);
	 else
		 throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__)); 
	
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
			case SDL_KEYDOWN:
				input->notifyOnKeyDown(event.key.keysym.scancode, deltaTime);
				break;
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

void    App::update(void) {
	// triangle->update();
	float currentFrame =(float)SDL_GetTicks() / 1000.0f; // SDL_GetTicks() returns milliseconds, so divide by 1000 to get seconds

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
	// camera->update();
}

void    App::render(void) {
	// triangle->render(camera->getView());
	model->render(camera->getView());
	SDL_GL_SwapWindow(window);
}

bool    App::isRunning(void) const {
    return (running);
}