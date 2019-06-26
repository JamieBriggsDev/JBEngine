#include "pch.h"
#include "Engine.h"


Engine::Engine()
{
	MyWindow = new Window();

	system("cls");
}

Engine::~Engine()
{
}

void Engine::MainLoop()
{
	// Get deltatime
	double lastTime = glfwGetTime();
	int totalFrames = 0;
	do {
		// Get delta time by comparing current time and last time
		double currentTime = glfwGetTime();
		m_deltaTime = float(currentTime - lastTime);

		// Update Window
		MyWindow->Update(m_deltaTime);

		// record new last time
		lastTime = currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while (MyWindow->CheckWindowClose() == 0);

}
