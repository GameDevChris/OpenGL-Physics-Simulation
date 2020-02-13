#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class GameObject
{
protected:
	glm::vec3 position;

public:
	GameObject();
	GameObject(glm::vec3 pos);
	~GameObject();

	virtual void Draw() = 0;
	virtual void Update(float);
};