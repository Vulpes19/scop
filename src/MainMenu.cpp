#include "MainMenu.hpp"

MainMenu::MainMenu(void)
{
	stateName = MainMenuState;

	numButtons = 2;
	selectedIndex = 1;
	
	initVertexData(TITLE);
	initVertexData(BUTTONN);

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

	
	textStart = FontLoader::getInstance()->getText("Roboto", "Start", SDL_Color {255, 255, 255, 0});
    if (textStart == UINT_MAX) {
		throw(ErrorHandler("Failed to get texture for: Start - " + std::string(TTF_GetError()), __FILE__, __LINE__));
	}

	textExit = FontLoader::getInstance()->getText("Roboto", "Exit", SDL_Color {255, 255, 255, 0});
    if (textExit == UINT_MAX) {
		throw(ErrorHandler("Failed to get texture for: Exit - " + std::string(TTF_GetError()), __FILE__, __LINE__));
	}

	textTitle = FontLoader::getInstance()->getText("Orbitron", "Scop", SDL_Color {86, 156, 214, 255});
    if (textTitle == UINT_MAX) {
		throw(ErrorHandler("Failed to get texture for: Title - " + std::string(TTF_GetError()), __FILE__, __LINE__));
	}

	shader->useShader();
	shader->setUniform("baseColor", Vector(45.0f / 255.0f, 45.0f / 255.0f, 48.0f / 255.0f));
	shader->setUniform("highlightColor", Vector(58.0f / 255.0f, 58.0f / 255.0f, 61.0f / 255.0f));
	shader->setUniform("textHighlightColor", Vector(86.0f / 255.0f, 156.0f / 255.0f, 214.0f / 255.0f));
	shader->setUniform("selectedIndex", selectedIndex);
	shader->setUniform("button", 1);
	shader->setUniform("isTitle", false);
	shader->setUniform("textTexture", textExit);

	projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity(); 

	projection.ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);

	modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");

}

MainMenu::~MainMenu(void)
{
	glDeleteTextures(1, &textStart);
	glDeleteTextures(1, &textExit);
	glDeleteTextures(1, &textTitle);
}

void	MainMenu::keyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera*)
{
	(void)deltaTime;
	if (InputDetector::getInstance()->isKeyPressed(key) && StatesManager::getInstance()->getCurrentState() == MainMenuState)
	{
		if (key == SDL_SCANCODE_UP)
		{
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

void	MainMenu::initVertexData(enum quadType type) {
	unsigned int	vertexArrayObject;
	unsigned int	vertexBufferObject;

	float quadVertices[] = {
		// positions   // texcoords
		1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};
	unsigned int indices[] = {  
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &EBO);

	glBindVertexArray(vertexArrayObject);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if (type == TITLE) {
		titleVAO = vertexArrayObject;
		titleVBO = vertexBufferObject;
	}
	else {
		VAO = vertexArrayObject;
		VBO = vertexBufferObject;
	}
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->useShader();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
    
	glBindVertexArray(titleVAO);
	shader->setUniform("isTitle", true);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textTitle);
	shader->setUniform("textTexture", 0);
	float titleWidth = 400.0f;
    float titleHeight = 200.0f;
    float x = (WIDTH - titleWidth) / 2.0f;
    float y = 50.0f; // 50px from the top
	model = model.identity();
    model.translate(Vector(x, y, 0.0f));
	model.scale(Vector(titleWidth, titleHeight, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
	glBindVertexArray(VAO);
	// start button
	shader->setUniform("isTitle", false);
	shader->setUniform("button", 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textStart);
	shader->setUniform("textTexture", 0);
	float btnWidth = 200.0f;
    float btnHeight = 50.0f;
    float x2 = (WIDTH - btnWidth) / 2.0f;
    float y2 = 300.0f; // place lower than title
	
	model = model.identity();
    model.translate(Vector(x2, y2, 0.0f));
	model.scale(Vector(btnWidth, btnHeight, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// exit button
	shader->setUniform("isTitle", false);
	shader->setUniform("button", 2);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textExit);
	shader->setUniform("textTexture", 0);
    float x3 = (WIDTH - btnWidth) / 2.0f;
    float y3 = 400.0f; // place lower than title
	
	model2 = Vulpes3D::Matrix4x4::identity();
    model2.translate(Vector(x3, y3, 0.0f));
	model2.scale(Vector(btnWidth, btnHeight, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model2.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}