#pragma once

#include "Window.h"
#include "Camera.h"
#include "ItemManager.h"
#include "DrawEngine.h"

class Engine
{
private:
	// Window object
	Window* m_myWindow;
	// Camera Object
	Camera* m_myCamera;
	// Controller Component
	Controller* m_myController;
	// Draw Engine
	DrawEngine* m_myDrawEngine;
	// Objects
	ItemManager<Object>* m_myObjects;
	// DeltaTime
	float m_deltaTime;
public:
	Engine();
	~Engine();
	void MainLoop();

};

