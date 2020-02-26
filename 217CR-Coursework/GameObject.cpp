#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

GameObject::GameObject()
{
}

GameObject::GameObject(glm::vec3 pos)
{
	position = pos;
	collider.colPosition = position;
	collider.radius = 0.6f;
}

GameObject::~GameObject()
{
}

void GameObject::CheckCollided()
{
	if (collided)
	{
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		currentColor = initialColor;
	}
}

void GameObject::Draw()
{
}

void GameObject::Update(float deltaTime)
{
	collider.colPosition = position;
	CheckCollided();
}
