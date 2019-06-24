#pragma once
// Window Resolution
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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

// Object Class
#include "Object.h"
// Camera Class
#include "Camera.h"

// Window class
class Window
{
private:
	GLFWwindow* window;
	//Shader* TempShader;
	//GLuint vertexbuffer;

	// To be moved
	GLuint MatrixID;
	//glm::mat4 MVP;

	// Camera Object
	Camera* m_myCamera;
	// Cube Object
	Object* m_cube;

	int Initialise();
public:
	Window();
	~Window();
	// Window Update Function.
	void Update();
	// Get window component.
	GLFWwindow* GetWindowComponent();
	// Check if the window is closing.
	int CheckWindowClose();

	// Static Resolution
	static int s_windowWidth;
	static int s_windowHeight;
};

