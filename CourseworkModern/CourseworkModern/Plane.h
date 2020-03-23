#pragma once
#include "GameObject.h"

class Plane : public GameObject
{
private:
	float vertices[66] = {
		 //Position				//Colour			//Texture		//Normals
		-0.5f,  0.0f, -0.5f,	0.8f, 0.8f, 0.0f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.0f, -0.5f,	0.8f, 0.8f, 0.0f,	1.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.0f,  0.5f,	0.8f, 0.8f, 0.0f,	1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.0f,  0.5f,	0.8f, 0.8f, 0.0f,	1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.0f,  0.5f,	0.8f, 0.8f, 0.0f,	0.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.0f, -0.5f,	0.8f, 0.8f, 0.0f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f
	};

public:
	Plane(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string tp);
	~Plane();
	void Draw();
	void Update(float deltaTime);
	void CreateBuffers();
};
