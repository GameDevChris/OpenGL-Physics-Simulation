#pragma once
#include "GameObject.h"
#include "RigidBody2D.h"
#include <iostream>
#include <vector>

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

