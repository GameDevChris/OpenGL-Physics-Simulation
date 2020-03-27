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
#include "Accessory.h";

class GameObject
{
public:

	//Name and state
	const char* name = "Name";
	string state;

	//Attributes
	glm::vec3 scale;
	glm::vec3 position;
	float speed = 1.0f;
	float rotSpeed = 1.0f;

	//Model
	std::string modelPath = "";
	Model* model;

	//Accessories
	Accessory* target;
	Accessory* thirdPerson;

	//Collider
	SphereCollider* collider;
	std::string colState = "dynamic";

	//Colors
	glm::vec3 currentColor;
	glm::vec3 initialColor = glm::vec3(1.0f, 1.0f, 1.0f);

	//Debug
	bool Debug = false;

	//Linear Movement
	float mass = 1.0f;
	glm::vec3 forceValue = glm::vec3(0, 0, 0);
	glm::vec3 linear_acceleration;
	glm::vec3 linear_velocity;
	glm::vec3 linear_totalForce;

	//Rotational Movement
	float inertia = 1.0f;
	glm::vec3 rotForceValue = glm::vec3(0, 0, 0);
	glm::vec3 orientation;
	glm::vec3 angular_acceleration;
	glm::vec3 angular_velocity;
	glm::vec3 angular_totalForce;

	//Collision
	float coefRest = 0.5f;
	bool collided = false;
	//SphereCollider collider;

	//Buffer
	unsigned int VBO, VAO;
	
	//Shader
	Shader myShader;

	//Optional textures (if model not loaded)
	unsigned int diffuseTexture;
	string diffuseTexturePath = "";
	unsigned int specTexture;
	string specTexturePath = "";

	//Constructors
	GameObject();
	GameObject(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col);

	//Destructor
	~GameObject();

	void CheckCollided();
	virtual void LoadModel();
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void CreateBuffers();
	virtual void CreateTextures();
	virtual void BindTexturesOnUnits();
};

