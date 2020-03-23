#pragma once
#include "GameObject.h"
class Sphere :
	public GameObject
{
	float vertices[2];

public:
	Sphere(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string tp);
	~Sphere();
	void Draw();
	void Update(float deltaTime);
	void CreateBuffers();
	void CreateVertices();

};

