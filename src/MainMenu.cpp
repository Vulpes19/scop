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
// 	float vertices[] = {
//     // x, y, z         u, v
//     740.0f, 300.0f, 0.0f,   1.0f, 0.0f,  // top-right -> u=1, v=0 (flipped)
//     740.0f, 250.0f, 0.0f,   1.0f, 1.0f,  // bottom-right -> u=1, v=1 (flipped)
//     500.0f, 250.0f, 0.0f,   0.0f, 1.0f,  // bottom-left -> u=0, v=1 (flipped)
//     500.0f, 300.0f, 0.0f,   0.0f, 0.0f,  // top-left -> u=0, v=0 (flipped)
// };
// float vertices[] = {
//     // Position your 71x34 text at (500,250)
//     571.0f, 284.0f, 0.0f,   1.0f, 0.0f,  // (500+71, 250+34)
//     571.0f, 250.0f, 0.0f,   1.0f, 1.0f,
//     500.0f, 250.0f, 0.0f,   0.0f, 1.0f,
//     500.0f, 284.0f, 0.0f,   0.0f, 0.0f,
// };

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

    
	// SDL_Surface *image = TextureLoader::getInstance()->getButton("start");
	text1 = FontLoader::getInstance()->getText("Prisma", "Start", textW, textH);
    if (text1 == UINT_MAX) {
		throw(ErrorHandler("Failed to get texture: ", __FILE__, __LINE__));
	}

	text2 = FontLoader::getInstance()->getText("Prisma", "Exit", textW, textH);
    if (text1 == UINT_MAX) {
		throw(ErrorHandler("Failed to get texture: ", __FILE__, __LINE__));
	}
	// glGenerateMipmap(GL_TEXTURE_2D);
	// text2 = FontLoader::getInstance()->getText("Prisma", "Exit", textW, textH);
    // if (text2 == UINT_MAX) {
	// 	throw(ErrorHandler("Failed to get texture: ", __FILE__, __LINE__));
	// }
//   glGenerateMipmap(GL_TEXTURE_2D);

	shader->useShader();
	shader->setUniform("baseColor", Vector(220.0f / 250.0f, 20.0f / 250.0f, 60.0f / 250.0f));
	shader->setUniform("highlightColor", Vector(1.0f, 1.0f, 1.0f));
	shader->setUniform("selectedIndex", selectedIndex);
	shader->setUniform("button", 1);
	shader->setUniform("textTexture", text2);

	projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity(); 

	projection.ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);

	modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");

}

MainMenu::~MainMenu(void)
{
	glDeleteTextures(1, &text1);
	glDeleteTextures(1, &text2);
}

void	MainMenu::keyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera*)
{
	(void)deltaTime;
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->useShader();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
    glBindVertexArray(VAO);
	
	// start button
	shader->setUniform("button", 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text1);
	shader->setUniform("textTexture", 0);
	model = model.identity();
	model.translate(Vector(0.0f, 50.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	shader->useShader();
	shader->setUniform("button", 2);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text2);
	shader->setUniform("textTexture", 0);
	model2 = Vulpes3D::Matrix4x4::identity();
	model2.translate(Vector(0.0f, 200.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model2.data());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}