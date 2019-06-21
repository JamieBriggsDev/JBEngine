// JBEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>

// Console input
#include <stdio.h>
#include <stdlib.h>


// Window
#include "Window.h"


int main()
{
    std::cout << "Welcome to the JBEngine!\n"; 

	Window MyWindow;

	do {

		MyWindow.Update();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(MyWindow.GetWindowComponent(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(MyWindow.GetWindowComponent()) == 0);


	return 0;
}
