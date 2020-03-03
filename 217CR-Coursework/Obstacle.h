#pragma once
#include "GameObject.h"
#include "SphereCollider.h"

class Obstacle : public GameObject
{
public:
	Obstacle(float m, float r, glm::vec3 position);
	~Obstacle();
	void Draw();
	void Update(float deltaTime);
};

