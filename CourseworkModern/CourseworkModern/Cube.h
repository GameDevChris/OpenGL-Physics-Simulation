#pragma once
#include "GameObject.h";


class Cube : public GameObject
{
private:
	float vertices[396];

public:
	Cube(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string dtp);
	Cube(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string dtp, std::string stp);
	~Cube();
	void Draw();
	void Update(float deltaTime);
	void CreateBuffers();
};

