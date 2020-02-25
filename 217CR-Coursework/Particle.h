#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
private:
	float mass;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 totalForce;

public:
	Particle(float m, glm::vec3 position);
	~Particle();
	void Draw();
	void Update(float);
	void CalculateForces(float deltaTime);
};

