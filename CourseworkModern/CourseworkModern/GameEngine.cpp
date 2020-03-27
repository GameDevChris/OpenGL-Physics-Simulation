#include "GameEngine.h"

//GameObject vector
std::vector<GameObject*> GameEngine::objects;

int GameEngine::controlMode = 1;
int GameEngine::boost = 1;
float GameEngine::cameraSpeed = 8.0f * deltaTime;

float GameEngine::deltaTime = 0.0f;
float GameEngine::lastFrame = 0.0f;

float GameEngine::diffuseStrength = 0.5f;
float GameEngine::specularStrength = 10.0f;

Camera GameEngine::mainCamera;
GameObject* GameEngine::mainSkybox;
GameObject* GameEngine::mainLight;
GameObject* GameEngine::mainPlayer;

bool GameEngine::Debug = false;

void GameEngine::UpdateGame()
{
	//Update Light diffuse and ambient
	glm::vec3 diffuseColor = mainLight->currentColor * glm::vec3(diffuseStrength);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	
	engineShader.Use();
	//Set material shininess
	engineShader.SetFloat("material.shininess", 256.0f);

	//Light Properties
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

	//Setup view and projection matrix
	engineShader.Use();
	CreateTransforms();

	//GameObjects Draw
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Debug = Debug;

		if(objects[i]->name == "Plane" && Debug == false)
		{
			continue;
		}

		else 
		{
			objects[i]->BindTexturesOnUnits();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(objects[i]->position.x, objects[i]->position.y, objects[i]->position.z));
			model = glm::rotate(model, -glm::radians(objects[i]->orientation.x), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, objects[i]->scale);

			engineShader.setMat4("model", model);

			objects[i]->Draw();
			objects[i]->Update(deltaTime);
		}
	}
	
	//GameObjects Collision check
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				if (objects[i]->collider != nullptr && objects[j]->collider != nullptr)
				{
					if (objects[i]->collider->CollideCheck(objects[j]->collider))
					{
						objects[i]->collided = true;
						objects[j]->collided = true;

						ColData Data;
						Data.GetColData(objects[i], objects[j]);
						Data.CalculateImpulse();
						Data.FixPenetration();
						Data.AddImpulse();
					}
					else
					{
						objects[i]->collided = false;
						objects[j]->collided = false;
					}
				}
			}
		}
	}

	//Draw Light
	engineShader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, mainLight->position);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::scale(model, mainLight->scale);
	engineShader.setMat4("model", model);
	mainLight->model->Draw(engineShader);

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
	//Create View Matrix
	//Free Roam Camera
	if (controlMode == 1)
	{
		view = glm::lookAt(glm::vec3(mainCamera.cameraPos),
			glm::vec3(mainCamera.cameraPos + mainCamera.cameraFront),
			glm::vec3(mainCamera.cameraUp));

		engineShader.setMat4("view", view);
		engineShader.setVec3("viewPos", mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);
	}

	//First Person Camera
	else if (controlMode == 2)
	{

		view = glm::lookAt(glm::vec3(mainPlayer->position.x, mainPlayer->position.y + 3, mainPlayer->position.z),
			mainPlayer->target->position,
			glm::vec3(0, 1, 0));

		engineShader.setMat4("view", view);
		engineShader.setVec3("viewPos", mainPlayer->position.x, mainPlayer->position.y + 3, mainPlayer->position.z);
	}

	//Third Person Camera
	else if (controlMode == 3)
	{
		view = glm::lookAt(mainPlayer->thirdPerson->position,
			mainPlayer->target->position,
			glm::vec3(0, 1, 0));

		engineShader.setMat4("view", view);
		engineShader.setVec3("viewPos", mainPlayer->thirdPerson->position.x, mainPlayer->thirdPerson->position.y, mainPlayer->thirdPerson->position.z);
	}

	//Top-Down Camera
	else if (controlMode == 4)
	{
		view = glm::lookAt(glm::vec3(0,20,0),
			glm::vec3(mainPlayer->position),
			glm::vec3(glm::vec3(0,1,0)));

		engineShader.setMat4("view", view);
		engineShader.setVec3("viewPos", 0, 20, 0);
	}

	//Create Projection Matrix
	projection = glm::perspective(glm::radians(mainCamera.fov), 960.0f / 540.0f, 0.1f, 100.0f);
	engineShader.setMat4("projection", projection);
}

void GameEngine::SetupLights(GameObject* ambientLight)
{
	//Assigning main light
	mainLight = ambientLight;
}

void GameEngine::SetupSkybox(GameObject* skybox)
{
	//Assigning skybox
	mainSkybox = skybox;
}

void GameEngine::CleanupEngine()
{
	//Delete VAOs, VBOs, objects and terminate window
	for (int i = 0; i < objects.size(); ++i)
	{
		glDeleteVertexArrays(1, &(objects[i]->VAO));
		glDeleteBuffers(1, &(objects[i]->VBO));
		delete objects[i];
	}

	glDeleteVertexArrays(1, &(mainLight->VAO));
	glDeleteBuffers(1, &(mainLight->VBO));
	delete mainLight;

	glDeleteVertexArrays(1, &(mainSkybox->VAO));
	glDeleteBuffers(1, &(mainSkybox->VBO));
	delete mainSkybox;

	glfwTerminate();
}

void GameEngine::ResizeWindow(GLFWwindow* window, int width, int height)
{
	//Resize window callback
	glViewport(0, 0, width, height);
}

void GameEngine::processInput(GLFWwindow* window)
{
	//Exit Game
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		CleanupEngine();
	}

	//Increase and decrease diffuse
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		diffuseStrength += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		diffuseStrength -= 0.1f;
	}

	//Increase and Decrease specular
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		specularStrength -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		specularStrength += 0.1f;
	}

	//WASD Movement for camera and hovercraft
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (controlMode == 1)
		{
			mainCamera.cameraPos += cameraSpeed * mainCamera.cameraFront;
		}
		else
		{
			//mainPlayer->forceValue +=  mainPlayer->playerFront * mainPlayer->speed; 
			mainPlayer->forceValue -= glm::vec3(1.0, 0.0, 0.0) * (mainPlayer->speed * boost); 
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
			mainPlayer->forceValue += glm::vec3(1.0, 0.0, 0.0) * (mainPlayer->speed * boost);
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

	//Camera modes
	//1 = Free Roam
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		controlMode = 1;
	}
	//2 = First Person Camera
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		controlMode = 2;
	}
	//3 = Third Person Camera
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		controlMode = 3;
	}
	//4 = Top-Down Camera
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		controlMode = 4;
	}

	//Boost
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (controlMode == 1)
		{
			cameraSpeed = 30.0f * deltaTime;
		}
		else
		{
			boost = 10;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		if (controlMode == 1)
		{
			cameraSpeed = 8.0f * deltaTime;
		}
		else
		{
			boost = 1;
		}
		
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Debug = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
	{
		Debug = false;
	}
}

void GameEngine::InitEngine()
{
	//Initialise GLFW
	glfwInit();
		
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set multisampling to 4 samples per fragment
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Create window
	window = glfwCreateWindow(960, 540, "Chris Bodsworth - 212/217 Coursework", NULL, NULL);
	mainCamera.gameWindow = window;
	if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
	glfwMakeContextCurrent(window);

	//Set Callbacks for window resize, mouse and scroll wheel
	glfwSetFramebufferSizeCallback(window, ResizeWindow);
	glfwSetCursorPosCallback(window, mainCamera.Mouse);
	glfwSetScrollCallback(window, mainCamera.Scroll);

	//Capture mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Load GLAD function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//Enable multisampling and depth test
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	//Build & Compile shader programs

		//Main engine shader
		engineShader = Shader("Vertex.vs", "Fragment.fs");
		engineShader.Start();
	
		//Skybox shader
		skyboxShader = Shader("ShaderVertex.vs", "ShaderFrag.fs");
		skyboxShader.Start();
}

void GameEngine::AddGameObject(GameObject* object)
{
	//Add object to vector
	objects.push_back(object);
}

void GameEngine::StartEngine()
{
	//Start Render loop
	while (!glfwWindowShouldClose(window))
	{
		UpdateGame();
	}
}

void GameEngine::Generate()
{
	//Assign shader, create buffers, textures, and load model for each GameObject
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->myShader = engineShader;
		objects[i]->CreateBuffers();
		objects[i]->CreateTextures();
		objects[i]->LoadModel();

		//Look for player and assign when found
		if (objects[i]->name == "Player")
		{
			mainPlayer = objects[i];
		}
	}
	
	//Create buffers, textures and model for light
	mainLight->CreateBuffers();
	mainLight->CreateTextures();
	mainLight->LoadModel();

	//Create buffers, textures and model for skybox
	mainSkybox->CreateBuffers();
	mainSkybox->CreateTextures();

	//Set material properties in shader
	engineShader.SetInt("material.texture_diffuse", GL_TEXTURE0);
	engineShader.SetInt("material.texture_specular", GL_TEXTURE1);
}


