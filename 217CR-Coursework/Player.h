#pragma once
#include "GameObject.h"
#include "SphereCollider.h"
class Player : public GameObject
{
private:
	float mass;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 totalForce;

public:
	Player(float m, glm::vec3 position);
	~Player();
	void Draw();
	void Update(float deltaTime);
};

