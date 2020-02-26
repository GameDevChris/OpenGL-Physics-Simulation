#include "Player.h"
#include <iostream>


Player::Player(float m, glm::vec3 position) : GameObject(position)
{
	mass = m;
	initialColor = glm::vec3(1.0f, 0.0f, 1.0f);
}

Player::~Player()
{
}

void Player::Draw()
{
	collider.Draw();

	glPushMatrix();
	glColor3f(currentColor.x, currentColor.y, currentColor.z);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();


}

void Player::Update(float deltaTime)
{
	collider.colPosition = position;
	CheckCollided();
	totalForce = glm::vec3(0.0f, 0.0f, 0.0f);

	if (GameObject::specialKeys[GLUT_KEY_UP])
	{
		totalForce += glm::vec3(0, 10,0);
	}

	if (GameObject::specialKeys[GLUT_KEY_DOWN])
	{
		totalForce += glm::vec3(0, -10, 0);
	}

	if (GameObject::specialKeys[GLUT_KEY_LEFT])
	{
		totalForce += glm::vec3(10, 0, 0);
	}

	if (GameObject::specialKeys[GLUT_KEY_RIGHT])
	{
		totalForce += glm::vec3(-10, 0, 0);
	}

	acceleration = totalForce / mass;
	position += velocity * deltaTime;
	velocity += acceleration * deltaTime;
	velocity *= pow(0.5, deltaTime);
}
