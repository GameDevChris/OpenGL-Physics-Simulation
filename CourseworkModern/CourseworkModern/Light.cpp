#include "Light.h"
using namespace std;

Light::Light(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string tp) : GameObject(m, rot, pos, sca, col)
{
	name = "Lamp";
	mass = m;
	orientation = rot;
	position = pos;
	scale = sca;
	diffuseTexturePath = tp;
	currentColor = col;

	float tempVertices[288] = {

		//position				//Colors						//Texture
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f
	};

	for (int i = 0; i < 288; ++i)
	{
		vertices[i] = tempVertices[i];
	}
}

Light::~Light()
{
}

void Light::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Light::CreateBuffers()
{
	//Vertex data & Buffers setup
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind VAO & VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure vertex attribute
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}
