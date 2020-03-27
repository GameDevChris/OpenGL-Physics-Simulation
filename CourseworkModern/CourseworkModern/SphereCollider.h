#pragma once
#include "Model.h";

class SphereCollider
{
public:
	float radius = 2.5f;

	glm::vec3 colPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(0.1f, 0.1f, 0.1f);

	Model* myModel;
	std::string modelPath;

	SphereCollider(std::string modPath, float rad);

	~SphereCollider();
	void Draw(Shader myShader);
	bool CollideCheck(SphereCollider* otherCol);
	void DrawRadius();
};

