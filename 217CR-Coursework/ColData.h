#pragma once
#include "GameObject.h"
#include <iostream>
#include <iomanip>
using namespace std;

struct ColData
{
	glm::vec3 colNormal;
	glm::vec3 colPoint;
	GameObject* obj1;
	GameObject* obj2;
	float penDepth;
	
	void GetColData(GameObject* object1, GameObject* object2)
	{

		obj1 = object1;
		obj2 = object2;
		
		float colDistance = sqrt(pow(object1->collider.colPosition.x - object2->collider.colPosition.x, 2) + pow(object1->collider.colPosition.y - object2->collider.colPosition.y, 2) + pow(object1->collider.colPosition.z - object2->collider.colPosition.z, 2));
		float colTotRad = object1->collider.radius + object2->collider.radius;

		colNormal = glm::normalize(object1->collider.colPosition - object2->collider.colPosition);
		penDepth = colTotRad - colDistance;
		colPoint = object1->collider.colPosition * colNormal * object1->collider.radius;

	}

	void PrintData() 
	{
		std::cout << std::setprecision(1);
		cout << "Col Normal: (" << colNormal.x << ", " << colNormal.y << ", " << colNormal.z << ") - " << " Col Point: (" << colPoint.x << ", " << colPoint.y << ", " << colPoint.z << ") - " << " Penetration Depth: " << penDepth << '\r';
	}
};