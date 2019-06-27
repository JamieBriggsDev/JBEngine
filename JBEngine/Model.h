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
	std::vector<glm::vec3> m_vertexBufferData;
	std::vector<glm::vec2> m_uvBufferData;

	// Vertex handle
	GLuint m_vertexArrayID;

	void BindBuffers();
	bool LoadObj(const char* _filePath,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs);
	void NormalizePositions(std::vector<glm::vec3> &out_vertices);
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

