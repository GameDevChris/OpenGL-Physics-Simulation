#pragma once
#pragma comment(lib, "glew32.lib")

#include "GameObject.h"
#include "RigidBody2D.h"
#include "Cube.h"
#include "Particle.h"
#include "Player.h"
#include "Obstacle.h"
#include "SphereCollider.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using namespace std;
class GameEngine
{ 
private:
	static std::vector<GameObject*> objects;
	static int oldTimeSinceStart;
	static int newTimeSinceStart;

	static void UpdateGame();
	static void DrawGame();
	static void CleanupEngine();
	static void ResizeWindow(int w, int h);

public:
	void InitEngine(int argc, char** argv, const char* windowTitle, int width, int height);
	void AddGameObject(GameObject*);
	void StartEngine();

};

