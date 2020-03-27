#include "GameEngine.h"

GameEngine engine;

//Uncomment for grass plane
GameObject* plane = new Plane(glm::vec3(0, -3, 0), glm::vec3(200, 1, 200), "./grass.jpg");

//Sun
GameObject* ambientLight = new Light("./Sun/Sun.obj");

//Skybox
GameObject* skybox = new Skybox();

//Player
GameObject* player = new Player(5, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(1, 1, 1), "./Hover/Hover/Hover.obj");

//Track
GameObject* track = new Track("./newTrack/Track.obj");

//Obstacle
GameObject* rock1 = new Obstacle("./Rock/Rock.obj", "dynamic", glm::vec3(10, 0, 10), glm::vec3(0.25, 0.25, 0.25));

GameObject* rock2 = new Obstacle("./Rock/Rock.obj", "dynamic", glm::vec3(-10, 0, -10), glm::vec3(0.25, 0.25, 0.25));

GameObject* rock3 = new Obstacle("./Rock/Rock.obj", "dynamic", glm::vec3(10, 0, -10), glm::vec3(0.25, 0.25, 0.25));

GameObject* rock4 = new Obstacle("./Rock/Rock.obj", "dynamic", glm::vec3(-10, 0, 10), glm::vec3(0.25, 0.25, 0.25));

GameObject* pole1 = new Obstacle("./Pole/Base/Base.obj", "static", glm::vec3(20, 0, 20), glm::vec3(0.08, 0.08, 0.08));

GameObject* pole2 = new Obstacle("./Pole/Base/Base.obj", "static", glm::vec3(-20, 0, -20), glm::vec3(0.08, 0.08, 0.08));

GameObject* pole3 = new Obstacle("./Pole/Base/Base.obj", "static", glm::vec3(20, 0, -20), glm::vec3(0.08, 0.08, 0.08));

GameObject* pole4 = new Obstacle("./Pole/Base/Base.obj", "static", glm::vec3(-20, 0, 20), glm::vec3(0.08, 0.08, 0.08));

int main()
{
	//Uncomment for grass plane
	engine.AddGameObject(plane);

	//Adding created GameObjects to vector
	engine.AddGameObject(player); 
	engine.AddGameObject(track);
	engine.AddGameObject(rock1);
	engine.AddGameObject(rock2);
	engine.AddGameObject(rock3);
	engine.AddGameObject(rock4);
	engine.AddGameObject(pole1);
	engine.AddGameObject(pole2);
	engine.AddGameObject(pole3);
	engine.AddGameObject(pole4);

	//Initializing engine
	engine.InitEngine();

	//Assigning main light and skybox
	engine.SetupLights(ambientLight);
	engine.SetupSkybox(skybox);

	//Generating objects
	engine.Generate();

	//Starting engine
	engine.StartEngine();
}
