#include "Accessory.h"

void Accessory::Draw(Shader myShader)
{
	myShader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

	if (modPath == "./Pole/Hoop/Hoop.obj")
	{
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	}


	if (modPath == "./Spinny/Spinny.obj")
	{
		model = glm::rotate(model, glm::radians(rot * 5), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	
	model = glm::scale(model, scale);
	myShader.setMat4("model", model);

	myModel->Draw(myShader);
}

Accessory::~Accessory()
{
}

Accessory::Accessory(std::string modelPath, glm::vec3 myScale)
{
	modPath = modelPath;
	scale = myScale;
	myModel = new Model(modelPath);
}
