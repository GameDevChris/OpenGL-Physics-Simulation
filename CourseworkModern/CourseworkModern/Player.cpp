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

	playerFront = glm::vec3(1.f, 0.f, 0.f);

	model = new Model(modelPath);
	spinny = new Accessory("./Spinny/Spinny.obj");
	target = new Accessory("./Target/target.obj");
	thirdPerson = new Accessory("./Target/target.obj");
	
}

Player::~Player()
{
}

void Player::LoadModel()
{
	cout << "loading craft" << endl;
	model->loadModel();
	spinny->myModel->loadModel();
	target->myModel->loadModel();
	thirdPerson->myModel->loadModel();
}

void Player::FindForward()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	playerFront = glm::normalize(direction);

	playerUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Player::Update(float deltaTime)
{
	//cout << "(" << linear_velocity.x << ", " << linear_velocity.y << ", " << linear_velocity.z << ")" << endl;
	//playerFront = glm::vec3(0.0f);
	
	target->scale = glm::vec3(0.05, 0.05, 0.05);
	thirdPerson->scale = glm::vec3(0.05, 0.05, 0.05);

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

	//Rotate force
	//cout << "Before Rotate (" << linear_totalForce.x << ", " << linear_totalForce.y << ", " << linear_totalForce.z << ")" << endl;
	
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(orientation.x), glm::vec3(0.0f, 1.0f, 0.0f));
	linear_totalForce =  linear_totalForce * glm::mat3(rotation);

	target->position = position;
	target->position += glm::vec3(-10,0,0) * glm::mat3(rotation);

	thirdPerson->position = position;
	thirdPerson->position += glm::vec3(0, 10, 0) * glm::mat3(rotation);
	thirdPerson->position += glm::vec3(20, 0, 0) * glm::mat3(rotation);
	//cout << "After Rotate (" << linear_totalForce.x << ", " << linear_totalForce.y << ", " << linear_totalForce.z << ")" << endl << endl;

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

void Player::DrawLines()
{
	float vertices[]{
		//Position																								        //Colour
		position.x, position.y, position.z,																			    1.0f, 0.0f, 0.0f,
		position.x + (playerFront.x*200) , position.y + (playerFront.y * 100), position.z + (playerFront.z * 100),		1.0f, 0.0f, 0.0f
	};

	unsigned int VAO, VBO;

	//Vertex data & Buffers setup
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind VAO & VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure vertex attribute
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
}

void Player::Draw()
{
	cout << "Drawing a " << name << endl;
	model->Draw(myShader);
	spinny->Draw(myShader);
	//target->Draw(myShader);
	//thirdPerson->Draw(myShader);
}

