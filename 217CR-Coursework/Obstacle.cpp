#include "Obstacle.h"

Obstacle::Obstacle(glm::vec3 position) : GameObject(position)
{
	initialColor = glm::vec3(0.0f, 0.0f, 1.0f);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{
	collider.Draw();

	glPushMatrix();
	glColor3f(currentColor.x, currentColor.y, currentColor.z);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();
}
