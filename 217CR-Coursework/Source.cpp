#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
#pragma comment(lib, "glew32.lib") 

#include "Cube.h"
#include "Particle.h"
#include "GameEngine.h"

GameObject* rb2D = new RigidBody2D(1.0f, 0.0f, 10.0f, 1.0f, glm::vec3(2, 0, 0));

GameEngine engine;

int main(int argc, char** argv)
{
	engine.InitEngine(argc, argv, "Ahhhhhhhhhh", 1000, 1000);
	engine.AddGameObject(rb2D);
	engine.StartEngine();

	return 0;
}