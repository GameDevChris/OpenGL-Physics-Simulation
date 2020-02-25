#pragma once
#include "GameObject.h"

class RigidBody2D : public GameObject
{
private:
	float mass;
	glm::vec3 linear_acceleration;
	glm::vec3 linear_velocity;
	glm::vec3 linear_totalForce;

	float inertia;
	float orientation;
	glm::vec3 angular_acceleration;
	glm::vec3 angular_velocity;
	glm::vec3 angular_totalForce;

	float length;
	float width;

public:
	RigidBody2D(float m, float r, float l, float w, glm::vec3 position);
	~RigidBody2D();
	void Draw();
	void Update(float);
	void CalculateForces(float deltaTime);

};

