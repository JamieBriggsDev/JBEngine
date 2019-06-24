#pragma once

#include <GL/glew.h>
#include "HardModels.h"

class Model
{
private:
	GLuint m_vertexBuffer;
	GLuint m_colorBuffer;
	GLuint m_vertexArrayID;
public:
	Model();
	~Model();
	// Get Vertex Buffer
	GLuint GetVertexBuffer();
	// Get Color Buffer
	GLuint GetColorBuffer();
};

