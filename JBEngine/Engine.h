#pragma once

#include "Window.h"
class Engine
{
private:
	Window* MyWindow;

public:
	Engine();
	~Engine();
	void MainLoop();
};

