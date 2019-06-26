#include "pch.h"
#include <objLoader.h>
#include "Model.h"

Model::Model()
{
	//m_vertexBufferData = g_cube_vertex_buffer_data;
	//m_uvBufferData = g_cube_uv_buffer_data;

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexBufferData.data()), m_vertexBufferData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_uvBufferData.data()), m_uvBufferData.data(), GL_STATIC_DRAW);
}

Model::Model(const char * _filePath)
{
	LoadObj(_filePath);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexBufferData.data()), m_vertexBufferData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_uvBufferData.data()), m_uvBufferData.data(), GL_STATIC_DRAW);
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

	//int TotalVertices = 0;


	//// Go through every mesh and count vertices
	//for (int i = 0; i < loader.LoadedMeshes.size(); i++)
	//{
	//	
	//	objl::Mesh mesh = loader.LoadedMeshes[i];
	//	TotalVertices += mesh.Vertices.size();





	//	// print mesh name
	//	//std::cout << i << ": " << mesh.MeshName << std::endl;

	//	//// Print mesh vertex details
	//	//for (int j = 0; j < mesh.Vertices.size(); j++)
	//	//{
	//	//	//std::cout << "P(" << mesh.Vertices[j].Position.X << "," <<
	//	//	//	mesh.Vertices[j].Position.Y << "," <<
	//	//	//	mesh.Vertices[j].Position.Z << ")\tN(" <<
	//	//	//	mesh.Vertices[j].Normal.X << "," <<
	//	//	//	mesh.Vertices[j].Normal.Y << "," <<
	//	//	//	mesh.Vertices[j].Normal.Z << ")\tUV(" <<
	//	//	//	mesh.Vertices[j].TextureCoordinate.X << "," <<
	//	//	//	mesh.Vertices[j].TextureCoordinate.Y << ")\n";
	//	//}
	//}

	const int TotalVertices = loader.LoadedVertices.size();

	//m_vertexBufferData = new float[TotalVertices * 3];
	//m_uvBufferData = new float[TotalVertices * 2];

	//std::cout << m_vertexBufferData << std::endl;
	//std::cout << sizeof(m_uvBufferData) << std::endl;

	for (int i = 0; i < loader.LoadedIndices.size(); i++)
	{
		int index = loader.LoadedIndices[i];
		// Add position data
		m_vertexBufferData.push_back(loader.LoadedVertices[index].Position.X);
		m_vertexBufferData.push_back(loader.LoadedVertices[index].Position.Y);
		m_vertexBufferData.push_back(loader.LoadedVertices[index].Position.Z);
		// Add UV data
		m_uvBufferData.push_back(loader.LoadedVertices[index].TextureCoordinate.X);
		m_uvBufferData.push_back(loader.LoadedVertices[index].TextureCoordinate.Y);
	}

	// Next initialize 

	std::cout << "Total Vertices: " << m_vertexBufferData.size() << std::endl;

	return true;
}