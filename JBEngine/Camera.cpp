#include "pch.h"
#include "Camera.h"
#include "Window.h"

Camera::Camera()
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), 
		(float)Window::s_windowWidth / Window::s_windowHeight,
		0.1f, 100.0f);
	// Camera View
	View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetProjectionView() 
{
	return Projection * View;
}