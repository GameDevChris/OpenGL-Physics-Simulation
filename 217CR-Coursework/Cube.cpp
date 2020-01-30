#include "Cube.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

Cube::Cube(glm::vec3 pos)
{
	position = pos;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(1.0f);
	glPopMatrix();
}
