#pragma once

// Console input
#include <stdio.h>
#include <stdlib.h>

// GLEW before everything else
#include <GL/glew.h>

// GLFW to handle window and keyboard/ mouse input
#include <GLFW/glfw3.h>

// Include GLM for the maths
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

// Shader Class
#include "Shader.h"

// Window class
class Window
{
private:
	GLFWwindow* window;
	Shader* TempShader;
	GLuint vertexbuffer;

	// To be moved
	GLuint MatrixID;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;

	int Initialise();
public:
	Window();
	~Window();
	void Update();
	GLFWwindow* GetWindowComponent();
	int CheckWindowClose();
};

