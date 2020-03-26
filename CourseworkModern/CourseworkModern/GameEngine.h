#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"
#include "Plane.h"
#include "Cube.h"
#include "Player.h"
#include "Track.h"
#include "Skybox.h"
#include "Obstacle.h"
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
	static vector<Model> models;
	static vector<GameObject*> cubes;
	static void CleanupEngine();
	static void ResizeWindow(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);

	static int controlMode;

public:	
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	GameObject* mainSkybox;
	GameObject* mainLight;
	static GameObject* mainPlayer;

	static float specularStrength;
	static float diffuseStrength;

	bool cubesPrepared;
	static float deltaTime;
	static float lastFrame;
	static Camera mainCamera;
	Shader engineShader;
	Shader skyboxShader;
    GLFWwindow* window;
	
	void InitEngine();
	void AddGameObject(GameObject*);
	void AddModel(Model);
	void StartEngine();
	void Generate();
	void UpdateGame();
	void CreateTransforms();
	void SortObjects();
	void SetupLights(GameObject* ambientLight);
	void SetupSkybox(GameObject* skybox);
	
};