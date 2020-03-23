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
}

Player::~Player()
{
}

void Player::FindForward()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	playerFront = glm::normalize(-direction);
}

void Player::Update(float deltaTime)
{
	//playerFront = glm::vec3(0.0f);
	model->position = position;
	//FindForward();
	//DrawLines();
	

	glm::vec3 forcePos = glm::vec3(0, 1, 0);

	glm::vec3 torque = degrees(glm::cross(forcePos, rotForceValue));

	inertia = 2 * (mass / 5) * (pow(0.5, 2));

	linear_totalForce = glm::vec3(0, 0, 0);
	linear_totalForce +=  forceValue * mass;

	linear_acceleration = linear_totalForce / mass;
	position += linear_velocity * deltaTime;

	linear_velocity += linear_acceleration * deltaTime;


	linear_velocity *= pow(0.5, deltaTime);

	angular_totalForce = glm::vec3(0, 0, 0);
	angular_totalForce += torque;
	angular_acceleration = angular_totalForce / inertia;
	orientation += angular_velocity.x * deltaTime;
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
