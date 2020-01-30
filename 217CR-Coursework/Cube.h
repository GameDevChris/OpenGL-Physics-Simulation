#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Cube
{
private:
	glm::vec3 position;

public:
	Cube(glm::vec3 pos);
	~Cube();

	void Draw();
};
