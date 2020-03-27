#include "SphereCollider.h"

SphereCollider::SphereCollider(std::string modPath, float rad)
{
	radius = rad;
	modelPath = modPath;
	scale = glm::vec3(radius, radius, radius);

	myModel = new Model(modelPath);
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Draw(Shader myShader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//DrawRadius();
	myShader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(colPosition.x, colPosition.y, colPosition.z));
	model = glm::scale(model, scale);
	myShader.setMat4("model", model);

	myModel->Draw(myShader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool SphereCollider::CollideCheck(SphereCollider* otherCol)
{
	float distance = sqrt(pow(colPosition.x - otherCol->colPosition.x, 2) + pow(colPosition.y - otherCol->colPosition.y, 2) + pow(colPosition.z - otherCol->colPosition.z, 2));

	float totalRadius = radius + otherCol->radius;

	//cout << "Distance: " << distance << " Radius: " << totalRadius << endl;
	return(distance <= totalRadius);
	//return(false);
}

void SphereCollider::DrawRadius()
{
	float vertices[]{
		//Position																								        //Colour
		colPosition.x, colPosition.y, colPosition.z,																	1.0f, 0.0f, 0.0f,
		colPosition.x, colPosition.y + radius, colPosition.z,															1.0f, 0.0f, 0.0f
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
