#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ColData.h"
#include "GameObject.h"
#include "Plane.h"
#include "Cube.h"
#include "Player.h"
#include "Track.h"
#include "Obstacle.h"
#include "Skybox.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include <iostream>
#include <vector>

using namespace std;
class GameEngine
{
private:
	static vector<GameObject*> objects;

	static int controlMode;
	static int boost;
	static float cameraSpeed;

	static float deltaTime;
	static float lastFrame;

	static float specularStrength;
	static float diffuseStrength;

	static Camera mainCamera;
	static GameObject* mainSkybox;
	static GameObject* mainLight;
	static GameObject* mainPlayer;

	static void CleanupEngine();
	static void ResizeWindow(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);

	static bool Debug;

public:	
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	
	Shader engineShader;
	Shader skyboxShader;
    GLFWwindow* window;
	
	void AddGameObject(GameObject*);
	void SetupLights(GameObject* ambientLight);
	void SetupSkybox(GameObject* skybox);
	void PrintControls();

	void InitEngine();
	void StartEngine();
	void Generate();
	void UpdateGame();
	void CreateTransforms();
};