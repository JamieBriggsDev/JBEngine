#pragma once

// Include GLM for the maths
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Window;
class Controller;

class Camera
{
private:
	glm::mat4 Projection;
	glm::mat4 m_viewMtx;

	// Camera angle
	float m_horizontalAngle = 3.14f;
	float m_verticalAngle = 0.0f;
	// Camera position
	glm::vec3 m_position = glm::vec3(0, 0, 5);
	// Camera speed
	float m_speed = 3.0f;
public:
	Camera();
	~Camera();
	glm::mat4 GetProjectionView();
	void Update(Window* _window, Controller* _controller, float _deltaTime);
};

