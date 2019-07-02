#pragma once

#include "Window.h"
#include "Camera.h"

class Engine
{
private:
	// Window object
	Window* m_myWindow;
	// Camera Object
	Camera* m_myCamera;
	// Controller Component
	Controller* m_myController;
	// DeltaTime
	float m_deltaTime;
public:
	Engine();
	~Engine();
	void MainLoop();
};

