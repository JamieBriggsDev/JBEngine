#pragma once

#include "Window.h"
class Engine
{
private:
	Window* MyWindow;
	float m_deltaTime;
public:
	Engine();
	~Engine();
	void MainLoop();
};

