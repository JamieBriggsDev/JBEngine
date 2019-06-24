#pragma once

// Include GLM for the maths
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::mat4 Projection;
	glm::mat4 View;
public:
	Camera();
	~Camera();
	glm::mat4 GetProjectionView();
};

