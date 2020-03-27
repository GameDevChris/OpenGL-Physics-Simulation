#pragma once
#include "GameObject.h"

struct ColData
{
	glm::vec3 colNormal;
	glm::vec3 colPoint;
	glm::vec3 displaceColObj1;
	glm::vec3 displaceColObj2;
	GameObject* obj1;
	GameObject* obj2;
	float penDepth;
	float Impulse;

	void GetColData(GameObject* object1, GameObject* object2)
	{

		obj1 = object1;
		obj2 = object2;

		float colDistance = sqrt(pow(object1->collider->colPosition.x - object2->collider->colPosition.x, 2) + pow(object1->collider->colPosition.y - object2->collider->colPosition.y, 2) + pow(object1->collider->colPosition.z - object2->collider->colPosition.z, 2));
		float colTotRad = object1->collider->radius + object2->collider->radius;

		colNormal = glm::normalize(object1->collider->colPosition - object2->collider->colPosition);
		penDepth = colTotRad - colDistance;
		colPoint = object1->collider->colPosition * colNormal * object2->collider->radius;

		displaceColObj1 = glm::vec3(colPoint.x - obj1->position.x, colPoint.y - obj1->position.y, colPoint.z - obj1->position.z);
		displaceColObj2 = glm::vec3(colPoint.x - obj2->position.x, colPoint.y - obj2->position.y, colPoint.z - obj2->position.z);

	}

	void CalculateImpulse()
	{
		float num = glm::dot(-(obj1->linear_velocity - obj2->linear_velocity), colNormal);
		num *= (1 + obj1->coefRest);

		float denum = glm::dot(colNormal, colNormal);
		denum *= (1 / obj1->mass + 1 / obj2->mass);

		//denum += ((glm::cross((glm::inverse(/*I thing*/) * glm::cross(displaceColObj1, colNormal)), displaceColObj1)) + ((glm::inverse(/*I thing*/) * glm::cross(displaceColObj2, colNormal)), displaceColObj2));

		Impulse = num / denum;
	}

	void AddImpulse()
	{
		if (obj1->colState == "dynamic") 
		{
			obj1->linear_velocity += (Impulse / obj1->mass) * colNormal;
		}
		
		if (obj2->colState == "dynamic")
		{
			obj2->linear_velocity -= (Impulse / obj1->mass) * colNormal;
		}
		//obj1->angular_velocity += glm::inverse(/*I thing*/) * (glm::cross(displaceColObj1 colNormal));
		//obj1->angular_velocity += glm::inverse(/*I thing*/) * (glm::cross(displaceColObj2 colNormal));
	}

	void FixPenetration()
	{
		if (obj1->colState == "dynamic")
		{
			obj1->position += penDepth * colNormal;
		}
		if (obj2->colState == "dynamic")
		{
			obj2->position -= penDepth * colNormal;
		}
	}

	void PrintData()
	{
		//std::cout << std::setprecision(1);
		//cout << "Col Normal: (" << colNormal.x << ", " << colNormal.y << ", " << colNormal.z << ") - " << " Col Point: (" << colPoint.x << ", " << colPoint.y << ", " << colPoint.z << ") - " << " Penetration Depth: " << penDepth << '\r';
	}
};

