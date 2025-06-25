#include "MainMenu.hpp"

MainMenu::MainMenu(void)
{
    std::cout << "currently Main Menu state" << std::endl;

	float vertices[] = {
		// x, y, z         u, v
		740.0f, 300.0f, 0.0f,   1.0f, 1.0f,
		740.0f, 250.0f, 0.0f,   1.0f, 0.0f,
		500.0f, 250.0f, 0.0f,   0.0f, 0.0f,
		500.0f, 300.0f, 0.0f,   0.0f, 1.0f,
	};

	unsigned int indices[] = {  
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};
	stateName = MainMenuState;
    #ifdef _WIN32
        shader = new Shader("C:\\Users\\asus\\Documents\\scop\\shaders\\MenuVertexShader.glsl", "C:\\Users\\asus\\Documents\\scop\\shaders\\MenuFragmentShader.glsl");
    #elif __APPLE__
        shader = new Shader("./shaders/MenuVertexShader.glsl", "./shaders/MenuFragmentShader.glsl");
    #elif __linux__
        shader = new Shader("./shaders/MenuVertexShader.glsl", "./shaders/MenuFragmentShader.glsl");
	#endif
	// label.addButtonType("MainMenu", 80, 200, { 136, 8, 8, 255 });
	// buttonsState["Play"] = FOCUS_ON;
	// buttonsState["Quit"] = FOCUS_OFF;

    shader->compileShader(GL_VERTEX_SHADER);
    shader->compileShader(GL_FRAGMENT_SHADER);
    shader->createShader();

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glGenTextures(1, &text1);
    glBindTexture(GL_TEXTURE_2D, text1);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// exit(1);
	SDL_Surface *text = FontLoader::getInstance()->getFont("Prisma", "Start");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text->w, text->h, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, text->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	glGenTextures(1, &text2);
	glBindTexture(GL_TEXTURE_2D, text2);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	SDL_Surface *text2 = FontLoader::getInstance()->getFont("Prisma", "Exit");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text2->w, text2->h, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, text2->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
	shader->useShader();
	shader->setUniform("baseColor", Vector(1.0f, 0.0f, 0.0));
    // shader->setUniform("useTexture", 0.0f);

	projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity(); 
	// projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	projection.ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);

	modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");

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
	glDisable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    shader->useShader();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
    glBindVertexArray(VAO);
	
	// first button
	model = model.identity();
	model.translate(Vector(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
	glBindTexture(GL_TEXTURE_2D, text1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// SECOND BUTTON
	model2 = Vulpes3D::Matrix4x4::identity();
	model2.translate(Vector(0.0f, -100.0f, 0.0f));
	// exit(1);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model2.data());
	glBindTexture(GL_TEXTURE_2D, text2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}