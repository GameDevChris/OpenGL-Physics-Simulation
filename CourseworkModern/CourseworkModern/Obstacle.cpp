#include "Obstacle.h"

Obstacle::Obstacle(std::string modpath, std::string state, glm::vec3 pos, glm::vec3 sca)
{
	name = "Obstacle";
	colState = state;
	position = pos;
	scale = sca;
	modelPath = modpath;
	model = new Model(modelPath);

	collider = new SphereCollider("./Sphere/Sphere.obj", 3.0f);
	spinny = new Accessory("./Pole/Hoop/Hoop.obj", glm::vec3(0.08f, 0.08f, 0.08f));
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{
	model->Draw(myShader);

	if (colState == "static")
	{
		spinny->Draw(myShader);
	}

	if (Debug)
	{
		collider->Draw(myShader);
	}
}

void Obstacle::Update(float deltaTime)
{
	spinny->position = position;
	collider->colPosition = position;

	glm::vec3 forcePos = glm::vec3(0, 1, 0);
	glm::vec3 forceValue = glm::vec3(0, 0, 0);

	glm::vec3 torque = degrees(glm::cross(forcePos, forceValue));

	inertia = 2 * (mass / 5) * (pow(0.5, 2));

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

void Obstacle::LoadModel()
{
	model->loadModel();
	spinny->myModel->loadModel();
	collider->myModel->loadModel();
}
