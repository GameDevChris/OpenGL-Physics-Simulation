#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "SphereCollider.h"
#include "Model.h";

class GameObject
{
public:

	const char* name = "Name";
	
	//Attributes
	glm::vec3 scale;
	glm::vec3 position;
	float speed = 1.0f;
	float rotSpeed = 1.0f;

	//Model
	std::string modelPath = "";
	Model* model;

	//Player directions
	float yaw = 0.0f;
	float pitch = 0.0f;
	static bool firstInput;
	glm::vec3 playerFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 playerUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//Colors
	glm::vec3 currentColor;
	glm::vec3 initialColor = glm::vec3(1.0f, 1.0f, 1.0f);

	//Linear Movement
	glm::vec3 forceValue = glm::vec3(0, 0, 0);
	float mass = 1.0f;
	glm::vec3 linear_acceleration;
	glm::vec3 linear_velocity;
	glm::vec3 linear_totalForce;

	//Rotational Movement
	glm::vec3 rotForceValue = glm::vec3(0, 0, 0);
	float inertia = 1.0f;
	glm::vec3 orientation;
	glm::vec3 angular_acceleration;
	glm::vec3 angular_velocity;
	glm::vec3 angular_totalForce;

	//Collision
	float coefRest = 0.5f;
	bool collided = false;
	SphereCollider collider;

	//Buffer
	unsigned int VBO, VAO;
	
	//Shader
	Shader myShader;

	GameObject(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col);
	
	//Optional textures
	unsigned int diffuseTexture;
	string diffuseTexturePath = "";

	unsigned int specTexture;
	string specTexturePath = "";

	~GameObject();

	void CheckCollided();
	void LoadModel();
	virtual void FindForward();
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void CreateBuffers();
	virtual void CreateTextures();
	virtual void BindTexturesOnUnits();
};

