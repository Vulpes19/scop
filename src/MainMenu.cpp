#include "MainMenu.hpp"

MainMenu::MainMenu(void)
{
	stateName = MainMenuState;

	numButtons = 2;
	selectedIndex = 1;
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
    #ifdef _WIN32
        shader = new Shader("C:\\Users\\asus\\Documents\\scop\\shaders\\MenuVertexShader.glsl", "C:\\Users\\asus\\Documents\\scop\\shaders\\MenuFragmentShader.glsl");
    #elif __APPLE__
        shader = new Shader("./shaders/MenuVertexShader.glsl", "./shaders/MenuFragmentShader.glsl");
    #elif __linux__
        shader = new Shader("./shaders/MenuVertexShader.glsl", "./shaders/MenuFragmentShader.glsl");
	#endif

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
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Repeat vertically
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	SDL_Surface *image = TextureLoader::getInstance()->getButton("start");
    if (!image)
		throw(ErrorHandler("Error failed to get button texture `start`", __FILE__, __LINE__));

	// Convert to a consistent format RGB
	SDL_Surface* converted = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGB24, 0);
	if (!converted) {
		throw(ErrorHandler("Failed to convert surface format", __FILE__, __LINE__));
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, converted->w, converted->h, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, converted->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	glGenTextures(1, &text2);
	glBindTexture(GL_TEXTURE_2D, text2);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Horizontal clamp
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Vertical clamp
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // Smooth minify
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	
	SDL_Surface *image2 = TextureLoader::getInstance()->getButton("exit");
	if (!image2)
		throw(ErrorHandler("Error failed to get button texture `exit`", __FILE__, __LINE__));
	// Convert to a consistent format RGB
	SDL_Surface* converted2 = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGB24, 0);
	if (!converted2) {
		throw(ErrorHandler("Failed to convert surface format", __FILE__, __LINE__));
	}
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, converted2->w, converted2->h, 0, 
             GL_RGB, GL_UNSIGNED_BYTE, converted2->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

	shader->useShader();
	shader->setUniform("baseColor", Vector(220.0f / 250.0f, 20.0f / 250.0f, 60.0f / 250.0f));
	shader->setUniform("highlightColor", Vector(1.0f, 1.0f, 1.0f));
	shader->setUniform("selectedIndex", selectedIndex);
	shader->setUniform("button", 1);

	projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity(); 

	projection.ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);

	modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");

	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);
	SDL_FreeSurface(converted);
	SDL_FreeSurface(converted2);
}

MainMenu::~MainMenu(void)
{
	glDeleteTextures(1, &text1);
	glDeleteTextures(1, &text2);
}

void	MainMenu::keyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera*)
{
	if (InputDetector::getInstance()->isKeyPressed(key) && StatesManager::getInstance()->getCurrentState() == MainMenuState)
	{
		if (key == SDL_SCANCODE_UP)
		{
			// selectedIndex = (selectedIndex - 1 + numButtons) % numButtons;
			selectedIndex = 1;
			shader->setUniform("selectedIndex", selectedIndex);
		}
		if (key == SDL_SCANCODE_DOWN)
		{
			selectedIndex = 2;
			shader->setUniform("selectedIndex", selectedIndex);
		}
		if (key == SDL_SCANCODE_RETURN && selectedIndex == 1)
		{
			StatesManager::getInstance()->addState(new ListScenesMenu());
			InputObserver* scenesObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
			if (scenesObserver)
				input->addObserver(scenesObserver);
			else
				throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__));
		}
		if (key == SDL_SCANCODE_RETURN && selectedIndex == 2) {
			StatesManager::getInstance()->removeState(input);
			return ;
		}
	}
}

void	MainMenu::mouseMove(Uint8 mouseButton, InputManager* input)
{
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
    // glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, text1);
    shader->useShader();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
    glBindVertexArray(VAO);
	
	// start button
	shader->setUniform("button", 1);
	model = model.identity();
	model.translate(Vector(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// exit button
	shader->useShader();
	shader->setUniform("button", 2);
    // glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, text2);
	model2 = Vulpes3D::Matrix4x4::identity();
	model2.translate(Vector(0.0f, 100.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model2.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}