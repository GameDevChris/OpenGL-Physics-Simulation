#include "Sphere.h"
using namespace std;

Sphere::Sphere(float m, glm::vec3 rot, glm::vec3 pos, glm::vec3 sca, glm::vec3 col, std::string tp) : GameObject(m, rot, pos, sca, col)
{
	name = "Sphere";
	position = pos;
	scale = sca;
	orientation = rot;
	currentColor = col;
}

Sphere::~Sphere()
{
}

void Sphere::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sphere::Update(float deltaTime)
{
}

void Sphere::CreateBuffers()
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void Sphere::CreateVertices()
{
}
