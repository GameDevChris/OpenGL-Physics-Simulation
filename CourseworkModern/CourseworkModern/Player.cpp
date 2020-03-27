#include "Player.h"

Player::Player(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string modp) : GameObject(m, rot, pos, sca, col)
{
	name = "Player";
	mass = m;
	orientation = rot;
	position = pos;
	scale = sca;
	initialColor = col;
	modelPath = modp;
	coefRest = 0.5f;
	speed = 5.0f;

	model = new Model(modelPath);
	spinny = new Accessory("./Spinny/Spinny.obj", glm::vec3(0.1f, 0.1f, 0.1f));
	target = new Accessory("./Target/target.obj", glm::vec3(0.05, 0.05, 0.05));
	thirdPerson = new Accessory("./Target/target.obj", glm::vec3(0.05, 0.05, 0.05));

	collider = new SphereCollider("./Sphere/Sphere.obj", 3.0f);
}

Player::~Player()
{
}

void Player::LoadModel()
{
	model->loadModel();
	spinny->myModel->loadModel();
	target->myModel->loadModel();
	thirdPerson->myModel->loadModel();

	collider->myModel->loadModel();
}

void Player::Update(float deltaTime)
{
	//cout << "(" << linear_velocity.x << ", " << linear_velocity.y << ", " << linear_velocity.z << ")" << endl;
	spinny->position = position;
	spinny->position.y -= 0.7;
	
	if (linear_velocity.x > 0.1) 
	{
		state = "moving";
		spinny->rot++;
	}

	else if (linear_velocity.x < -0.1)
	{
		state = "moving";
		spinny->rot--;
	}

	else
	{
		state = "idle";
		spinny->rot = 0;
	}
	
	glm::vec3 forcePos = glm::vec3(0, 1, 0);

	glm::vec3 torque = glm::cross(forcePos, rotForceValue);

	inertia = 2 * (mass / 5) * (pow(0.5, 2));

	linear_totalForce = glm::vec3(0, 0, 0);
	linear_totalForce += forceValue * mass;

	//cout << "(" << orientation.x << ", " << orientation.y << ", " << orientation.z << ")" << endl;

	
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(orientation.x), glm::vec3(0.0f, 1.0f, 0.0f));

	//Use Rotation to move elements local to object
		linear_totalForce =  linear_totalForce * glm::mat3(rotation);

		target->position = position;
		target->position += glm::vec3(-10,0,0) * glm::mat3(rotation);

		thirdPerson->position = position;
		thirdPerson->position += glm::vec3(0, 10, 0) * glm::mat3(rotation);
		thirdPerson->position += glm::vec3(20, 0, 0) * glm::mat3(rotation);

		collider->colPosition = position;
		collider->colPosition += glm::vec3(1, 0, 0) * glm::mat3(rotation);

	
	linear_acceleration = linear_totalForce / mass;
	position += linear_velocity * deltaTime;

	linear_velocity += linear_acceleration * deltaTime;


	linear_velocity *= pow(0.5, deltaTime);

	angular_totalForce = glm::vec3(0, 0, 0);
	angular_totalForce += torque;
	angular_acceleration = angular_totalForce / inertia;
	orientation.x += glm::degrees(angular_velocity.x * deltaTime);
	angular_velocity += angular_acceleration * deltaTime;
	angular_velocity *= pow(0.5, deltaTime);
	
	forceValue = glm::vec3(0, 0, 0);
	rotForceValue = glm::vec3(0, 0, 0);
}

void Player::Draw()
{
	model->Draw(myShader);
	spinny->Draw(myShader);

	if (Debug) 
	{
		collider->Draw(myShader);
		target->Draw(myShader);
		thirdPerson->Draw(myShader);
	}
}

