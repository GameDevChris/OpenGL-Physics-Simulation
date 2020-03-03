#include "Player.h"
#include <iostream>


Player::Player(float m, float r, glm::vec3 position) : GameObject(m ,r, position)
{
	initialColor = glm::vec3(1.0f, 0.0f, 1.0f);
	radius = 0.5f;
	coefRest = 0.5f;
	speed = 5.0f;
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
		glRotatef(orientation, 0, 0, 1);
		glutSolidSphere(radius, 10, 10);
	glPopMatrix();
}

void Player::Update(float deltaTime)
{
	collider.radius = radius + 0.1f;
	collider.colRotation = orientation;
	collider.colPosition = position;
	CheckCollided();

	glm::vec3 forcePos = glm::vec3(0, 5, 0);
	glm::vec3 forceValue = glm::vec3(0, 0, 0);

	if (GameObject::specialKeys[GLUT_KEY_LEFT])
	{
		forceValue += glm::vec3(1 * speed, 0, 0);
	}

	if (GameObject::specialKeys[GLUT_KEY_RIGHT])
	{
		forceValue += glm::vec3(-1 * speed, 0, 0);
	}

	if (GameObject::specialKeys[GLUT_KEY_UP])
	{
		forceValue += glm::vec3(0, 1 * speed, 0);
	}

	if (GameObject::specialKeys[GLUT_KEY_DOWN])
	{
		forceValue += glm::vec3(0, -1 * speed, 0);
	}

	glm::vec3 torque = degrees(glm::cross(forcePos, forceValue));

	inertia = 2*(mass / 5) * (pow(0.5, 2));

	linear_totalForce = glm::vec3(0, 0, 0);
	linear_totalForce += 5.0f * forceValue * mass;
	linear_acceleration = linear_totalForce / mass;
	position += linear_velocity * deltaTime;
	linear_velocity += linear_acceleration * deltaTime;
	linear_velocity *= pow(0.5, deltaTime);

	angular_totalForce = glm::vec3(0, 0, 0);
	angular_totalForce += torque;
	angular_acceleration = angular_totalForce / inertia;
	orientation += angular_velocity.z * deltaTime;
	angular_velocity += angular_acceleration * deltaTime;
	angular_velocity *= pow(0.5, deltaTime);
}
