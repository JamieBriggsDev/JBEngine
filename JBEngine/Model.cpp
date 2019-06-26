#include "pch.h"
#include <objLoader.h>
#include "Model.h"

Model::Model()
{
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_uv_buffer_data), g_cube_uv_buffer_data, GL_STATIC_DRAW);
}

Model::Model(const char * _filePath)
{
	LoadObj(_filePath);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_uv_buffer_data), g_cube_uv_buffer_data, GL_STATIC_DRAW);
}


Model::~Model()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	//glDeleteBuffers(1, &m_colorBuffer);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

// Get Vertex Buffer
GLuint Model::GetVertexBuffer() 
{ 
	return m_vertexBuffer; 
}

// Get UV Buffer
GLuint Model::GetUVBuffer() 
{
	return m_uvBuffer;
}

bool Model::LoadObj(const char * _filePath)
{
	// Initialize the OBJ Loader
	objl::Loader loader;
	// Load a .obj file
	if(!loader.LoadFile(_filePath))
		return false;



	return true;
}