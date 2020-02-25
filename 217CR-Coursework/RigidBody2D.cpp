#include "RigidBody2D.h"
#include <iostream>

RigidBody2D::RigidBody2D(float m, float r, float l, float w, glm::vec3 position) : GameObject(position)
{
	mass = m;
	linear_velocity = glm::vec3(0, 0, 0);
	linear_acceleration = glm::vec3(0, 0, 0);
	linear_totalForce = glm::vec3(0, 0, 0);
	orientation = r;
	angular_acceleration = glm::vec3(0, 0, 0);
	angular_velocity = glm::vec3(0, 0, 0);
	angular_totalForce = glm::vec3(0, 0, 0);

	length = l;
	width = w;
}

RigidBody2D::~RigidBody2D()
{
}

void RigidBody2D::Draw()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(orientation, 0, 0, 1);
		glColor3f(1.f, 1.f, 1.f);

		glBegin(GL_QUADS);
			glVertex3f(-length, width, 0);
			glVertex3f(length, width, 0);
			glVertex3f(length, -width, 0);
			glVertex3f(-length, -width, 0);
		glEnd();

		glPointSize(5.0f);
		glColor3f(0.f, 0.f, 0.f);
		glBegin(GL_POINTS);
			glVertex3f(0, 0, 0);
		glEnd();

	glPopMatrix();
}

void RigidBody2D::Update(float deltaTime)
{
	CalculateForces(deltaTime);
	std::cout << orientation << std::endl;
}

void RigidBody2D::CalculateForces(float deltaTime)
{
	glm::vec3 forcePos = glm::vec3(1, 1, 0);
	glm::vec3 forceValue = glm::vec3(2, 0, 0);
	glm::vec3 torque = degrees(glm::cross(forcePos, forceValue));
	inertia = (mass/12) * (pow(length,2) + pow(width,2));

	linear_totalForce = glm::vec3(0, 0, 0);
	linear_totalForce += forceValue * mass;
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
