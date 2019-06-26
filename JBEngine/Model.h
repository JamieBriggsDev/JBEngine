#pragma once

#include <GL/glew.h>
#include <vector>
#include "HardModels.h"

class Model
{
private:
	// Buffers
	GLuint m_vertexBuffer;
	GLuint m_uvBuffer;

	// Buffer Data
	std::vector<float> m_vertexBufferData;
	std::vector<int> m_uvBufferData;

	// Vertex handle
	GLuint m_vertexArrayID;

	bool LoadObj(const char* _filePath);
public:
	// Default constructor
	Model();
	// Constructor which loads .obj file
	Model(const char* _filePath);

	~Model();
	// Get Vertex Buffer
	GLuint GetVertexBuffer();
	// Get UV Buffer
	GLuint GetUVBuffer();
};

