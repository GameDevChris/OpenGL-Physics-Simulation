#include "GameObject.h"
using namespace std;

GameObject::GameObject()
{
}

GameObject::GameObject(float m, glm::vec3 r, glm::vec3 pos, glm::vec3 sca, glm::vec3 col)
{
}

GameObject::~GameObject()
{
}

void GameObject::CheckCollided()
{
}

void GameObject::LoadModel()
{
	if (modelPath != "")
	{
		model->loadModel();
	}
}

void GameObject::Draw()
{
	model->Draw(myShader);
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::CreateBuffers()
{
	
}

void GameObject::CreateTextures()
{
	//Diffuse
	if (diffuseTexturePath != "")
	{
		glGenTextures(1, &diffuseTexture);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(diffuseTexturePath.c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, diffuseTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		stbi_image_free(data);
	}

	//Specular
	if (specTexturePath != "")
	{
		glGenTextures(1, &specTexture);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(specTexturePath.c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, specTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}
		stbi_image_free(data);
	}
	
}

void GameObject::BindTexturesOnUnits()
{
	if (diffuseTexture != 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	}

	if (specTexture != 0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specTexture);
	}
}