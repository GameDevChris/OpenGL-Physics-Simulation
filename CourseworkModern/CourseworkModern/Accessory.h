#pragma once
#include "Model.h";

class Accessory
{
public:
	float rot = 0;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(0.1f, 0.1f, 0.1f);
	Model* myModel;
	void Draw(Shader myShader);
	Accessory(std::string modelPath, glm::vec3 myScale);
	~Accessory();
};

