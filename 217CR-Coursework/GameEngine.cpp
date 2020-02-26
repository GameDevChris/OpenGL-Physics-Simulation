#include "GameEngine.h"

std::vector<GameObject*> GameEngine::objects;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;

void GameEngine::UpdateGame()
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

void GameEngine::DrawGame()
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

void GameEngine::CleanupEngine()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
	}
}

void GameEngine::ResizeWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GameEngine::InitEngine(int argc, char** argv, const char* windowTitle, int width, int height)
{
	glutInit(&argc, argv);

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(windowTitle);

	glewExperimental = GL_TRUE;
	glewInit();

	glutDisplayFunc(DrawGame);
	glutReshapeFunc(ResizeWindow);
	glutIdleFunc(UpdateGame);

	glutKeyboardFunc([](unsigned char key, int x, int y)
		{
			GameObject::keys[key] = true;

			switch (key)
			{
				case 27:
					CleanupEngine;
					exit(0);
					break;

				case 'w':
					break;

				case 's':
					break;

				case 'a':
					break;

				case 'd':
					break;

				default:
					break;
			}
		});
	glutKeyboardUpFunc([](unsigned char key, int x, int y)
		{
			GameObject::keys[key] = false;
		});

	glutSpecialFunc([](int key, int x, int y) 
		{
			GameObject::specialKeys[key] = true;

			switch (key)
			{
				case GLUT_KEY_UP:
					break;
				case GLUT_KEY_DOWN:
					break;
				case GLUT_KEY_LEFT:
					break;
				case GLUT_KEY_RIGHT:
					break;
				default:
					break;
			}
		});
	glutSpecialUpFunc([](int key, int x, int y) 
		{
			GameObject::specialKeys[key] = false;
		});
}

void GameEngine::AddGameObject(GameObject* object)
{
	objects.push_back(object);
}

void GameEngine::StartEngine()
{
	glutMainLoop();
}
