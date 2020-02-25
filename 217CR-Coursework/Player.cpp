#include "Player.h"

#include <iostream>

Player::Player(float m, glm::vec3 position) : GameObject(position)
{
	mass = m;
}

Player::~Player()
{
}

void Player::Draw()
{
	glPushMatrix();
	glColor3f(1.f, 0.f, 1.0f);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();
}

void Player::Update(float deltaTime)
{
	totalForce = glm::vec3(0.0f, 0.0f, 0.0f);

	if (GameObject::specialKeys[GLUT_KEY_UP])
	{
		std::cout << "I've Been called!" << std::endl;
		totalForce += glm::vec3(0, 0, 5);
	}

	if (GameObject::specialKeys[GLUT_KEY_DOWN])
	{
		totalForce += glm::vec3(0, 0, -5);
	}

	acceleration = totalForce / mass;
	position += velocity * deltaTime;
	velocity += acceleration * deltaTime;
	velocity *= pow(0.5, deltaTime);
}
