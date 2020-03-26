#include "GameEngine.h"

std::vector<GameObject*> GameEngine::objects;
std::vector<Model> GameEngine::models;
std::vector<GameObject*> GameEngine::cubes;

int GameEngine::controlMode;
float GameEngine::deltaTime;
float GameEngine::lastFrame;
float GameEngine::diffuseStrength;
float GameEngine::specularStrength;
Camera GameEngine::mainCamera;
GameObject* GameEngine::mainPlayer;

void GameEngine::UpdateGame()
{
	

	glm::vec3 diffuseColor = mainLight->currentColor * glm::vec3(diffuseStrength);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	
	engineShader.Use();

	//Material Properties
	engineShader.SetFloat("material.shininess", 256.0f);

	//Light Properties1
	engineShader.setVec3("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
	engineShader.setVec3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
	engineShader.setVec3("light.specular", specularStrength, specularStrength, specularStrength);
	engineShader.setVec3("light.position", mainLight->position.x, mainLight->position.y, mainLight->position.z);

	//Time
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//Inputs
	processInput(window);

	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	engineShader.Use();

	CreateTransforms();


	//Draw Light
	engineShader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, mainLight->position);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	model = glm::scale(model, mainLight->scale);
	engineShader.setMat4("model", model);
	mainLight->model->Draw(engineShader);
	
	
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->BindTexturesOnUnits();
		
		//if (objects[i]->state == "moving")
		//{
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, glm::vec3(objects[i]->position.x, objects[i]->position.y, objects[i]->position.z));

			model = glm::rotate(model, -glm::radians(objects[i]->orientation.x), glm::vec3(0.0f, 1.0f, 0.0f));

			model = glm::scale(model, objects[i]->scale);

			engineShader.setMat4("model", model);
		//}

		//else if (objects[i]->state == "idle"
		//}
		//cout << "There are " << objects.size() << " objects to be loaded" << endl;

		objects[i]->Draw();
		objects[i]->Update(deltaTime);
		cout << endl;
	}
	
	//Skybox
	glDepthFunc(GL_LEQUAL);
	skyboxShader.Use();
	view = glm::mat4(glm::mat3(view));
	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);
	mainSkybox->Draw();
	glDepthFunc(GL_LESS);

	//Swap buffers & poll IO events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void GameEngine::CreateTransforms()
{
	//View Matrix
	if (controlMode == 1)
	{
		view = glm::lookAt(glm::vec3(mainCamera.cameraPos),
			glm::vec3(mainCamera.cameraPos + mainCamera.cameraFront),
			glm::vec3(mainCamera.cameraUp));
	}

	else if (controlMode == 2)
	{

		view = glm::lookAt(glm::vec3(mainPlayer->position.x, mainPlayer->position.y + 3, mainPlayer->position.z),
			mainPlayer->target->position,
			glm::vec3(0, 1, 0));
	}

	else if (controlMode == 3)
	{
		view = glm::lookAt(mainPlayer->thirdPerson->position,
			mainPlayer->target->position,
			glm::vec3(0, 1, 0));
	}

	else if (controlMode == 4)
	{
		view = glm::lookAt(glm::vec3(0,20,0),
			glm::vec3(mainPlayer->position),
			glm::vec3(glm::vec3(0,1,0)));
	}

	engineShader.setMat4("view", view);
	engineShader.setVec3("viewPos", mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);

	//Projection Matrix
	projection = glm::perspective(glm::radians(mainCamera.fov), 1920.0f / 1080.0f, 0.1f, 100.0f);
	
	engineShader.setMat4("projection", projection);
}

void GameEngine::SortObjects()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->name == "Cube")
		{
			cout << "Generating a " << objects[i]->name << endl;
			cubes.push_back(objects[i]);
		}
	}

	cout << "Generating " << cubes.size() << "cubes" << endl;
}

void GameEngine::SetupLights(GameObject* ambientLight)
{
	mainLight = ambientLight;
	
}

void GameEngine::SetupSkybox(GameObject* skybox)
{
	mainSkybox = skybox;
}

void GameEngine::CleanupEngine()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		glDeleteVertexArrays(1, &(objects[i]->VAO));
		glDeleteBuffers(1, &(objects[i]->VAO));
		delete objects[i];
		
	}
	glfwTerminate();
}

void GameEngine::ResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GameEngine::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		CleanupEngine();
	}

	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		diffuseStrength += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		diffuseStrength -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		specularStrength -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		specularStrength += 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (controlMode == 1)
		{
			mainCamera.cameraPos += cameraSpeed * mainCamera.cameraFront;
		}
		else
		{
			//mainPlayer->forceValue +=  mainPlayer->playerFront * mainPlayer->speed; 
			mainPlayer->forceValue -= glm::vec3(1.0, 0.0, 0.0) *mainPlayer->speed; 
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (controlMode == 1)
		{
			mainCamera.cameraPos -= cameraSpeed * mainCamera.cameraFront;
		}
		else
		{
			//mainPlayer->forceValue -=  mainPlayer->playerFront * mainPlayer->speed;
			mainPlayer->forceValue += glm::vec3(1.0, 0.0, 0.0) * mainPlayer->speed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (controlMode == 1)
		{
			mainCamera.cameraPos -= glm::normalize(glm::cross(mainCamera.cameraFront, mainCamera.cameraUp)) * cameraSpeed;
		}
		else
		{
			mainPlayer->rotForceValue -= glm::vec3(1.0, 1.0, 1.0) * mainPlayer->rotSpeed;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (controlMode == 1)
		{
			mainCamera.cameraPos += glm::normalize(glm::cross(mainCamera.cameraFront, mainCamera.cameraUp)) * cameraSpeed;
		}
		else
		{
			mainPlayer->rotForceValue += glm::vec3(1.0, 1.0, 1.0) * mainPlayer->rotSpeed;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		controlMode = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		controlMode = 2;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		controlMode = 3;
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		controlMode = 4;
	}
}

void GameEngine::InitEngine()
{
	controlMode = 1;
	diffuseStrength = 0.5f;
	specularStrength = 1.0f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;

	cout << "Starting Engine..." << endl;

	//Initialise GLFW
	cout << "Initialising GLFW..." << endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Create window
	cout << "Creating window..." << endl;
	window = glfwCreateWindow(1920, 1080, "Ahhhhhh", NULL, NULL);
	mainCamera.gameWindow = window;
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, ResizeWindow);
	glfwSetCursorPosCallback(window, mainCamera.Mouse);
	glfwSetScrollCallback(window, mainCamera.Scroll);

	//Capture mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Load GLAD function pointers
	cout << "Loading GLAD function pointers..." << endl;
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	//Build & Compile shader program
	cout << "Creating shader program..." << endl;
	engineShader = Shader("Vertex.vs", "Fragment.fs");
	engineShader.Start();

	skyboxShader = Shader("ShaderVertex.vs", "ShaderFrag.fs");
	skyboxShader.Start();
}

void GameEngine::AddGameObject(GameObject* object)
{
	objects.push_back(object);
}

void GameEngine::AddModel(Model model)
{
	models.push_back(model);
}

void GameEngine::StartEngine()
{
	while (!glfwWindowShouldClose(window))
	{
		UpdateGame();
	}
}

void GameEngine::Generate()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		cout << "Generating a " << objects[i]->name << endl;
		objects[i]->CreateBuffers();
		objects[i]->CreateTextures();
		objects[i]->myShader = engineShader;
		objects[i]->LoadModel();

		if (objects[i]->name == "Player")
		{
			mainPlayer = objects[i];
			cout << "Found player" << endl;
		}
	}
	
	mainLight->CreateBuffers();
	mainLight->CreateTextures();
	mainLight->LoadModel();

	mainSkybox->CreateBuffers();
	mainSkybox->CreateTextures();

	engineShader.SetInt("material.texture_diffuse", GL_TEXTURE0);
	engineShader.SetInt("material.texture_specular", GL_TEXTURE1);

	skyboxShader.Use();
	skyboxShader.SetInt("skybox", 0);
}


