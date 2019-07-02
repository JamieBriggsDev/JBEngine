#include "pch.h"
#include "Engine.h"
#include "Controller.h"

// Disable nSight unknown object warning

Engine::Engine()
{
	// Create Window
	m_myWindow = new Window();
	// Create Controller
	m_myController = new Controller();
	// Create Camera
	m_myCamera = new Camera();
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
		totalFrames++;
		//std::cout << currentTime << "   " << lastTime << std::endl;
		if (currentTime - lastTime >= 0.001) { // If last prinf() was more than 1 sec ago
		 // printf and reset timer
			//printf("%f ms/frame\n", 100.0 / double(totalFrames));
			totalFrames = 0;
			lastTime += 1.0;
		}

		// Update controller
		m_myController->Update(m_myWindow, m_deltaTime);

		// Update the camera
		m_myCamera->Update(m_myWindow, m_myController, m_deltaTime);

		// Update Window
		m_myWindow->Update(m_myCamera, m_deltaTime);

		// record new last time
		lastTime = currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while (m_myWindow->CheckWindowClose(m_myController) == 0);

}
