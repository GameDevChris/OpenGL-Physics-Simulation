#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera 
{
private:
	
	static float mouseLastX;
	static float mouseLastY;
	static float yaw;
	static float pitch;
	static bool firstInput;

public:
	GLFWwindow* gameWindow;
	glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	static float fov;

	Camera();
	~Camera();
	static void Mouse(GLFWwindow* window, double xpos, double ypos);
	static void Scroll(GLFWwindow* window, double xoffset, double yoffset);
};

