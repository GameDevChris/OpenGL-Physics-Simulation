#include "SphereCollider.h"

SphereCollider::SphereCollider()
{

}


SphereCollider::SphereCollider(float r, glm::vec3 pos)
{
	radius = r;
	colPosition = pos;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Draw()
{
	glPushMatrix();
		glColor3f(0.f, 1.f, 0.f); 
		glTranslatef(colPosition.x, colPosition.y, colPosition.z);
		glRotatef(colRotation, 0, 0, 1);
		glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

bool SphereCollider::CollideCheck(SphereCollider& otherCol)
{
	float distanceVector = sqrt(pow(colPosition.x - otherCol.colPosition.x, 2) + pow(colPosition.y - otherCol.colPosition.y, 2) + pow(colPosition.z - otherCol.colPosition.z, 2));
	
	//float distanceVector = 3;

	//float xdiffSquared = pow(colPosition.x - otherCol.colPosition.x, 2);
	
	
	float totalRadius = radius + otherCol.radius;

	return(distanceVector <= totalRadius);
}


