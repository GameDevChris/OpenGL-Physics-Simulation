#pragma once
#include "GameObject.h"
#include "SphereCollider.h"
class Player : public GameObject
{
public:
	Player(float m, float r, glm::vec3 position);
	~Player();
	void Draw();
	void Update(float deltaTime);
};

