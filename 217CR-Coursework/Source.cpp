#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
#pragma comment(lib, "glew32.lib") 

#include "Cube.h"
#include <iostream>
#include <vector>

vector<GameObject*> objects;

GameObject* cube = new Cube(glm::vec3(1, 0, 0));
GameObject* cube2 = new Cube(glm::vec3(3, 0, 1));

int oldTimeSinceStart = 0;
int newTimeSinceStart = 0;



// Drawing routine.
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	objects.push_back(cube);
	objects.push_back(cube2);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	GameObject::keys[key] = true;

	switch (key)
	{
	case 27:
		for (int i = 0; i < objects.size(); ++i)
		{
			delete objects[i];
		}
		exit(0);
		break;
	case 'w':
		cout << "Moving forward in - Z" << endl;
		break;
	case 's':
		cout << "Moving backward in + Z" << endl;
		break;
	case 'a':
		cout << "Moving left in - X" << endl;
		break;
	case 'd':
		cout << "Moving right in + X" << endl;
		break;
	default:
		break;
	}
}

void keyInputUp(unsigned char key, int x, int y)
{
	GameObject::keys[key] = false;
}

void keySpecialInput(int key, int x, int y)
{
	cout << "input down" << endl;
	GameObject::specialKeys[key] = true;

	switch (key)
	{
	case GLUT_KEY_UP:
		cout << "Moving forward in - Z" << endl;
		break;
	case GLUT_KEY_DOWN:
		cout << "Moving backward in +Z" << endl;
		break;
	case GLUT_KEY_LEFT:
		cout << "Moving left in -X" << endl;
		break;
	case GLUT_KEY_RIGHT:
		cout << "Moving right in +X" << endl;
		break;
	default:
		break;
	}
}

void keySpecialInputUp(int key, int x, int y)
{
	cout << "input up" << endl;
	GameObject::specialKeys[key] = false;
}

void idle()
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	
	deltaTime /= 1000.f;

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

	glutPostRedisplay();
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Week 1 - Basic Scene");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutKeyboardUpFunc(keyInputUp);
	glutSpecialFunc(keySpecialInput);
	glutSpecialUpFunc(keySpecialInputUp);
	glutIdleFunc(idle);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}