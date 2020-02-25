#include "Particle.h"

Particle::Particle(float m, glm::vec3 position) : GameObject(position)
{
	mass = m;
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
}

Particle::~Particle()
{
}

void Particle::Draw()
{
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.f, 0.f, 1.f);
	glBegin(GL_LINES);
	glVertex3f(position.x, position.y, position.z);
	glVertex3f(position.x + velocity.x, position.y + velocity.y, position.z + velocity.z);
	glEnd();
	glPopMatrix();
}

void Particle::Update(float deltaTime)
{
	CalculateForces(deltaTime);
}

void Particle::CalculateForces(float deltaTime) 
{
	totalForce = glm::vec3(0, 0, 0);
	totalForce += glm::vec3(0, -9.8f, 0) * mass;
	acceleration = totalForce / mass;
	position += velocity * deltaTime;
	velocity += acceleration * deltaTime;
}
