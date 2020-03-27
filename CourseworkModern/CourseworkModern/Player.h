#pragma once
#include "GameObject.h"


class Player : public GameObject
{
public:
	Accessory* spinny;
	Accessory* turbine;
	Player(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string modp);
	~Player();
	void LoadModel();
	void Update(float deltaTime);
	void Draw();
};

