#include "pch.h"
#include "Window.h"

// Error codes
#define W_GLFW_FAILED_TO_INITIALISE -100
#define W_WINDOW_FAILED_TO_OPEN -101
#define W_COULD_NOT_INITIALISE_GLEW -102

// To be removed!!
static const GLfloat g_vertex_buffer_data[] = {
-1.0f, -1.0f, 0.0f,
 1.0f, -1.0f, 0.0f,
 0.0f,  1.0f, 0.0f,
};

Window::Window()
{
	Initialise();
}

Window::~Window()
{
}

int Window::Initialise()
{	
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	// Try to initialise
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return W_GLFW_FAILED_TO_INITIALISE;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "JBEngine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return W_WINDOW_FAILED_TO_OPEN;
	}

	// Initialize GLEW
	glfwMakeContextCurrent(window); 
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return W_COULD_NOT_INITIALISE_GLEW;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	TempShader = new Shader("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return 1;
}

void Window::Update()
{

	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);

	// Use shader
	glUseProgram(TempShader->GetProgramID());

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

}

GLFWwindow* Window::GetWindowComponent()
{
	return window;
}

int Window::CheckWindowClose()
{
	// returns false if ESC not pressed or window isn't attempting to 
	//  close.
	return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window);
}
