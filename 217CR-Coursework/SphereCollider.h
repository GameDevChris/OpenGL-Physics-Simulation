#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class SphereCollider
{
public:
	float radius = 1.0f;
	glm::vec3 colPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	float colRotation = 0;

	SphereCollider();
	SphereCollider(float r, glm::vec3 pos);

	~SphereCollider();
	void Draw();
	bool CollideCheck(SphereCollider& otherCol);
};

