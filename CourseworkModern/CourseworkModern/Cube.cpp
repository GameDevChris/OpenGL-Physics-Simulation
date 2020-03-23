#include "Cube.h"
using namespace std;

Cube::Cube(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string dtp) : GameObject(m, rot, pos, sca, col)
{
	name = "Cube";
	position = pos;
	scale = sca;

	currentColor = col;


	float tempVertices[396] = {

		//position				//Colors											//Texture		//Normals
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  1.0f,  0.0f
	};

	for (int i = 0; i < 396 ; ++i)
	{
		vertices[i] = tempVertices[i];
	}
	
}

Cube::Cube(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string dtp, std::string stp) : GameObject(m, rot, pos, sca, col)
{
	name = "Cube";
	position = pos;
	scale = sca;

	currentColor = col;

	orientation = rot;

	float tempVertices[396] = {

		//position				//Colors						//Texture		//Normals
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		-1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	currentColor.x, currentColor.y, currentColor.z,		0.0f, 1.0f,		0.0f,  1.0f,  0.0f
	};

	for (int i = 0; i < 396; ++i)
	{
		vertices[i] = tempVertices[i];
	}

}

Cube::~Cube()
{
}

void Cube::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	//Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//cout << color.x << " " << color.y << " " << color.z << endl;
}

void Cube::Update(float deltaTime)
{
}

void Cube::CreateBuffers()
{
	cout << "Setting up cube buffer..." << endl;
	//Vertex data & Buffers setup
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	cout << "	Binding VAO & VBO..." << endl;
	//Bind VAO & VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	cout << "	Configuring vertex attributes..." << endl;
	//Configure vertex attribute
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Normal attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
}
