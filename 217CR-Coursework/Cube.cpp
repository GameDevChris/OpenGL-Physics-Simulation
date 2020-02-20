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

void Cube::Update(float deltaTime)
{
	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		position.z += 1.f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		position.z -= 1.f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		position.x -= 1.f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		position.x += 1.f * deltaTime;
}
