#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>
#include "SphereCollider.h"

class GameObject
{
protected:
	glm::vec3 position;
	glm::vec3 currentColor;
	glm::vec3 initialColor = glm::vec3(1.0f, 1.0f, 1.0f);
	

public:
	bool collided = false;
	SphereCollider collider;
	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;
	GameObject();
	GameObject(glm::vec3 pos);
	~GameObject();

	void CheckCollided();
	virtual void Draw();
	virtual void Update(float);
};