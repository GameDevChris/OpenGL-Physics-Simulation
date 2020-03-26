#include "Track.h"

Track::Track(std::string modp)
{
	name = "Track";
	position = glm::vec3(0, -1.5, 0);
	scale = glm::vec3(0.2, 0.2, 0.2);
	modelPath = modp;
	model = new Model(modelPath);
}

Track::~Track()
{
}
