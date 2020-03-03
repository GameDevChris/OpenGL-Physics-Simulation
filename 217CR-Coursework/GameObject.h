#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>
#include "SphereCollider.h"
//#include "ColData.h"

class GameObject
{
public:
	float speed = 1.0f;
	float radius = 1.0f;
	glm::vec3 position;
	glm::vec3 currentColor;
	glm::vec3 initialColor = glm::vec3(1.0f, 1.0f, 1.0f);

	float mass = 1.0f;
	glm::vec3 linear_acceleration;
	glm::vec3 linear_velocity;
	glm::vec3 linear_totalForce;

	float inertia = 1.0f;
	float orientation = 1.0f;
	glm::vec3 angular_acceleration;
	glm::vec3 angular_velocity;
	glm::vec3 angular_totalForce;

	float coefRest = 0.5f;

	bool collided = false;
	SphereCollider collider;
	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;
	GameObject();
	GameObject(glm::vec3 pos);
	GameObject(float m, float r, glm::vec3 pos);
	~GameObject();

	void CheckCollided();
	virtual void Draw();
	virtual void Update(float);
};