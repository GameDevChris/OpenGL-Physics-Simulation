#include "Cube.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

Cube::Cube()
{
}

Cube::Cube(glm::vec3 pos): GameObject(pos)
{
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
