#pragma once
#include "GameObject.h"


class Player : public GameObject
{
public:
	Accessory* spinny;
	Player(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string modp);
	~Player();
	void LoadModel();
	void FindForward();
	void Update(float deltaTime);
	void DrawLines();
	void Draw();
};

