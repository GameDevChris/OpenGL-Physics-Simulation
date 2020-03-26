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
	Plane(glm::vec3 pos, glm::vec3 sca, std::string texPath);
	~Plane();
	void Draw();
	void CreateBuffers();
};
