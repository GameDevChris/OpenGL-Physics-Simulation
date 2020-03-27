#pragma once
#include "GameObject.h"
class Obstacle : public GameObject
{
public:
	Obstacle(std::string modpath, std::string state, glm::vec3 pos, glm::vec3 sca);
	~Obstacle();
	void Draw();
	void Update(float deltaTime);
	void LoadModel();
};

