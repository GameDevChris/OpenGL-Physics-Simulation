#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <string>
#include "GameEngine.h"

GameEngine engine;


//GameObject* cube = new Cube(5.0f, 0.0f, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1.0f, 0.5f, 0.0f), "./martin.jpg");
//GameObject* cube2 = new Cube(5.0f, 0.0f, glm::vec3(1.5, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), "./luke.jpg");

//GameObject* cube3 = new Cube(5.0f, 0.0f, glm::vec3(-1.5, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), "./vlad.jpg");
//GameObject* cube4 = new Cube(5.0f, 0.0f, glm::vec3(-3, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 1), "./tay.jpg");
//GameObject* cube5 = new Cube(5.0f, 0.0f, glm::vec3(3, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0), "./george.jpg");
//GameObject* cube6 = new Cube(5.0f, 0.0f, glm::vec3(0, 0, 2), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0), "./mia.jpg");

//GameObject* testCube = new Cube(5.0f, 0.0f, glm::vec3(0, 0, -3), glm::vec3(5,5, 5), glm::vec3(1, 1, 1), "./container2.jpg", "./container2_specular.jpg");
//GameObject* testCube = new Cube(5.0f, 0.0f, glm::vec3(0, 0.5, -1), glm::vec3(3, 3, 3), glm::vec3(1, 1, 1), "./container2.jpg", "./container2_specular.jpg");

//GameObject* richardCube = new Cube(5.0f, 0.0f, glm::vec3(1, 0, 3), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0), "./richard.jpg");

//GameObject* plane = new Plane(5.0f, 0.0f, glm::vec3(0, -0.017, 0), glm::vec3(5, 5, 5), glm::vec3(1, 1, 1), "./ollie.jpg");
//GameObject* plane2 = new Plane(5.0f, 45.0f, glm::vec3(0, -0.4, -0.4), glm::vec3(5, 5, 5), glm::vec3(1, 1, 1), "./evans2.jpg");

GameObject* ambientLight = new Light(5.0f, glm::vec3(0, 0, 0), glm::vec3(0, 1, 3), glm::vec3(1, 1, 1), glm::vec3(1.0f, 1.0f, 1.0f), "./lamp.jpg");

GameObject* player = new Player(5, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.2, 0.2), glm::vec3(1, 1, 1), "./Hover/Hover.obj");


int main()
{
	/*engine.AddGameObject(cube);
	engine.AddGameObject(cube2);
	engine.AddGameObject(cube3);
	engine.AddGameObject(cube4);
	engine.AddGameObject(cube5);
	engine.AddGameObject(cube6);
	engine.AddGameObject(testCube);
	engine.AddGameObject(richardCube);
	engine.AddGameObject(plane);
	engine.AddGameObject(plane2);*/

	engine.AddGameObject(player); 

	engine.InitEngine();
	engine.SetupLights(ambientLight);
	//Model scorpion("./Hover/Hover.obj");
	//engine.AddModel(scorpion);
	//Model track("./Track/Track.obj");
	//engine.AddModel(track);
	engine.Generate();
	engine.StartEngine();
}