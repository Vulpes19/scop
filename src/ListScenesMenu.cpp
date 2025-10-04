#include "ListScenesMenu.hpp"

ListScenesMenu::ListScenesMenu(void)
{
	getModels();
	selectedIndex = 0;
	float vertices[] = {
		// pos         // texCoord
		300.0f, 150.0f, 0.0f,  1.0f, 1.0f,
		300.0f, 0.0f,   0.0f,  1.0f, 0.0f,
		0.0f,   0.0f,   0.0f,  0.0f, 0.0f,
		0.0f,   150.0f, 0.0f,  0.0f, 1.0f,
	};
	unsigned int indices[] = {  
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};
	stateName = ListScenesMenuState;
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

	shader->useShader();
	shader->setUniform("baseColor", Vector(45.0f / 255.0f, 45.0f / 255.0f, 48.0f / 255.0f));
	shader->setUniform("highlightColor", Vector(58.0f / 255.0f, 58.0f / 255.0f, 61.0f / 255.0f));
	shader->setUniform("textHighlightColor", Vector(86.0f / 255.0f, 156.0f / 255.0f, 214.0f / 255.0f));
	shader->setUniform("selectedIndex", selectedIndex);
	shader->setUniform("button", 1);

	projection = Vulpes3D::Matrix4x4::identity();
    model = Vulpes3D::Matrix4x4::identity(); 

	projection.ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);

	modelLoc = shader->getUniformLoc("model");
    projectionLoc = shader->getUniformLoc("projection");

}

ListScenesMenu::~ListScenesMenu(void)
{}

void	ListScenesMenu::keyDown(SDL_Scancode key, float deltaTime, InputManager *input, Camera *camera)
{
	(void)deltaTime;
	if (InputDetector::getInstance()->isKeyPressed(key) && StatesManager::getInstance()->getCurrentState() == ListScenesMenuState)
	{
		if (key == SDL_SCANCODE_RIGHT)
		{
			selectedIndex += 1;
			if ((size_t)selectedIndex == modelPaths.size() || selectedIndex == 6)
				selectedIndex = 0;
			shader->setUniform("selectedIndex", selectedIndex);
		}
		if (key == SDL_SCANCODE_LEFT)
		{
			selectedIndex -= 1;
			if (selectedIndex == -1)
				selectedIndex = modelPaths.size() - 1;
			shader->setUniform("selectedIndex", selectedIndex);
		}
		if (key == SDL_SCANCODE_RETURN)
		{
			std::string strPath = modelPaths[selectedIndex];
			std::string ID = strPath.substr(16);
			ID.erase(ID.find(".obj"));
			StatesManager::getInstance()->addState(new Scene(ID, camera->getPosition()));
			InputObserver* levelObserver = dynamic_cast<InputObserver*>(StatesManager::getInstance()->getCurrentStateInstance());
			if (levelObserver)
				input->addObserver(levelObserver);
			else
				throw(ErrorHandler("Can't cast state to an observer, causes the input to not work: ", __FILE__, __LINE__));
		}
		if (key == SDL_SCANCODE_ESCAPE) {
			StatesManager::getInstance()->removeState(input);
			return ;
		}
	}
}


void	ListScenesMenu::handleInput(void)
{

}

void	ListScenesMenu::update(float)
{

}

void	ListScenesMenu::render(Vulpes3D::Matrix4x4)
{
	glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->useShader();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
    glBindVertexArray(VAO);
	
	int buttonId = 0;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 3; ++i) {
			/* load text texture for the button*/
			glActiveTexture(GL_TEXTURE0);
			auto it = buttonTexts.find(modelPaths[buttonId]);
			GLint text = it->second;
			glBindTexture(GL_TEXTURE_2D, text);

			/* positioning the button */
			model = Vulpes3D::Matrix4x4::identity();
			float yPadding = (j == 0) ? 50.0f : 400.0f;
			model.translate(Vector(i * 500.0f, yPadding, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());

			/* set button id uniform and selectedIndex to highlight the selected button */
			shader->setUniform("button", buttonId);
			shader->setUniform("selectedIndex", selectedIndex);  // This one changes with key input
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			buttonId += 1;
			if (modelPaths.size() - 1 < (size_t)buttonId || 5 < (size_t)buttonId)
				break;
		}
	}
}

void ListScenesMenu::getModels(void) {
	DIR *directory = opendir("./assets/models/");
    struct dirent *dir;

    if (directory == NULL) {
        throw(ErrorHandler("Error opening directory /assets/models to load models", __FILE__, __LINE__));
    }
    while ((dir = readdir(directory)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
			std::string modelName = std::string(dir->d_name);
			/* get full path of .obj model file */
            std::string fullPath = "./assets/models/" + modelName;
			/* load text texture for each button */
			unsigned int text = FontLoader::getInstance()->getText("Prisma", (modelName.erase(modelName.find(".obj"))).c_str(), SDL_Color {255, 255, 255, 0});
			if (text == UINT_MAX) {
				throw(ErrorHandler("Failed to get texture for: " + modelName + " - " + std::string(TTF_GetError()), __FILE__, __LINE__));
			}
			buttonTexts[fullPath] = FontLoader::getInstance()->getText("Prisma", modelName.c_str(), SDL_Color {255, 255, 255, 0});

            modelPaths.push_back(fullPath);
        }
    }
    (void)closedir(directory);
}
