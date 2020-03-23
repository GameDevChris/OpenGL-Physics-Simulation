#include "Camera.h"
float Camera::mouseLastX;
float Camera::mouseLastY;
float Camera::yaw;
float Camera::pitch;
float Camera::fov;
bool Camera::firstInput;
glm::vec3 Camera::cameraFront;

Camera::Camera()
{
	mouseLastX = 400;
	mouseLastY = 300;
	yaw = -90.0f;
	pitch = 0.0f;
	fov = 45.0f;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	firstInput = true;
}

Camera::~Camera()
{
}

void Camera::Mouse(GLFWwindow* window, double xpos, double ypos)
{
	if (firstInput)
	{
		mouseLastX = xpos;
		mouseLastY = ypos;
		firstInput = false;
	}

	float DeltaX = xpos - mouseLastX;
	float DeltaY = -ypos + mouseLastY;
	mouseLastX = xpos;
	mouseLastY = ypos;

	const float sensitivity = 0.2f;
	DeltaX *= sensitivity;
	DeltaY *= sensitivity;

	yaw += DeltaX;

	pitch += DeltaY;
	if (pitch > 89.0f) { pitch = 89.0f; }
	if (pitch < -89.0f) { pitch = -89.0f; }

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void Camera::Scroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov > 1.0f && fov < 45.0f)
		fov -= yoffset;
	else if (fov <= 1.0f)
		fov = 2.0f;
	else if (fov >= 45.0f)
		fov = 44.0f;
}
