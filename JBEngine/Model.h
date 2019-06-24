#pragma once

#include <GL/glew.h>
#include "HardModels.h"

class Model
{
private:
	// Buffers
	GLuint m_vertexBuffer;
	GLuint m_uvBuffer;
	// Vertex handle
	GLuint m_vertexArrayID;
public:
	Model();
	~Model();
	// Get Vertex Buffer
	GLuint GetVertexBuffer();
	// Get UV Buffer
	GLuint GetUVBuffer();
};

