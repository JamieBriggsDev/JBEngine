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

class Window
{
private:
	GLFWwindow* window;

	int Initialise();
public:
	Window();
	~Window();
	void Update();
	GLFWwindow* GetWindowComponent();
};

