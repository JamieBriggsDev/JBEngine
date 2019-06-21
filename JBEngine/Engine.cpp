#include "pch.h"
#include "Engine.h"


Engine::Engine()
{
	MyWindow = new Window();
}

Engine::~Engine()
{
}

void Engine::MainLoop()
{
	do {

		// Update Window
		MyWindow->Update();

	} // Check if the ESC key was pressed or the window was closed
	while (MyWindow->CheckWindowClose() == 0);

}
