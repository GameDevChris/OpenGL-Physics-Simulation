#include "Light.h"
using namespace std;

Light::Light(std::string modp)
{
	currentColor = glm::vec3(1, 1, 1);
	name = "Lamp";
	position = glm::vec3(0, 100, 0);
	scale = glm::vec3(0.5, 0.5, 0.5);
	modelPath = modp;
	model = new Model(modelPath);
}

Light::~Light()
{
}
