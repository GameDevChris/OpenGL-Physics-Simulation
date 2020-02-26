#pragma once
#include "GameObject.h"
#include "SphereCollider.h"

class Obstacle : public GameObject
{
public:
	Obstacle(glm::vec3 position);
	~Obstacle();
	void Draw();
};

