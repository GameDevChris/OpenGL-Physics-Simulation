#include "GameEngine.h"

//GameObject* rb2D = new RigidBody2D(1.0f, 0.0f, 2.0f, 0.2f, glm::vec3(2, 0, 0));
GameObject* player = new Player(5.0f, 0.0f,  glm::vec3(0, 0, 0));
GameObject* obstacle = new Obstacle(5.0f, 0.0f, glm::vec3(3, 0, 0));

GameEngine engine;

int main(int argc, char** argv)
{
	engine.InitEngine(argc, argv, "Ahhhhhhhhhh", 1000, 1000);
	engine.AddGameObject(obstacle);
	engine.AddGameObject(player);
	engine.StartEngine();

	return 0;
}