#pragma once
#include "GameObject.h";

class Light : public GameObject
{
private:
	float vertices[288];

public:
	Light(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string tp);
	~Light();
	virtual void Draw();
	void CreateBuffers();
};

