#include "pch.h"
#include <objLoader.h>
#include <glm/glm.hpp>

//#define TINYOBJLOADER_IMPLEMENTATION
//#include <tiny_obj_loader.h>

#include "Model.h"
#include "Vertex.h"

Model::Model()
{
	//m_vertexBufferData = g_cube_vertex_buffer_data;
	//m_uvBufferData = g_cube_uv_buffer_data;
	m_vertexBufferData.clear();
	m_uvBufferData.clear();

	// copy arrays into vectors
	m_vertexBufferData.insert(m_vertexBufferData.end(),
		&g_cube_vertex_buffer_data[0],
		&g_cube_vertex_buffer_data[sizeof(g_cube_vertex_buffer_data)]);
	m_uvBufferData.insert(m_uvBufferData.end(),
		&g_cube_uv_buffer_data[0],
		&g_cube_uv_buffer_data[sizeof(g_cube_uv_buffer_data)]);

	BindBuffers();
}

Model::Model(const char * _objFilePath)
{
	//LoadObjOld(_filePath, m_vertexBufferData, m_uvBufferData);
	LoadObj(_objFilePath, m_vertexBufferData, m_uvBufferData, m_normalBufferData);

	BindBuffers();
}


Model::~Model()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	//glDeleteBuffers(1, &m_colorBuffer);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Model::BindBuffers()
{
	// Bind IDs
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	// Get buffer sizes
	int vertexBufferSize = m_vertexBufferData.size() * sizeof(glm::vec3);
	int uvBufferSize = m_uvBufferData.size() * sizeof(glm::vec2);
	int normalBufferSize = m_normalBufferData.size() * sizeof(glm::vec3);
	// Bind Vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &m_vertexBufferData[0], GL_STATIC_DRAW);
	// Bind UV buffer
	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvBufferSize, &m_uvBufferData[0], GL_STATIC_DRAW);
	// Bind Normal buffer
	glGenBuffers(1, &m_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normalBufferSize, &m_normalBufferData[0], GL_STATIC_DRAW);
}

// Get Indices Count
GLuint Model::GetIndicesCount()
{
	return m_totalIndices;
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

// Get Normal Buffer
GLuint Model::GetNormalBuffer()
{
	return m_normalBuffer;
}

bool Model::LoadObj(const char * _filePath, 
	std::vector<glm::vec3>& out_vertices, 
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	// Clear vertices and UVS
	out_vertices.clear();
	out_uvs.clear();
	out_normals.clear();

	printf("Loading OBJ file %s...\n", _filePath);

	std::vector<unsigned int> temp_indices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	// Initialise obj loader
	objl::Loader MyLoader;
	
	if (!MyLoader.LoadFile(_filePath) ){
		printf("Can't Open obj. file!\n");
		return false;
	}

	for (const auto& mesh : MyLoader.LoadedMeshes)
	{
		for (const auto& vertex : mesh.Vertices)
		{
			glm::vec3 position;
			position.x = vertex.Position.X;
			position.y = vertex.Position.Y;
			position.z = vertex.Position.Z;
			temp_vertices.push_back(position);

			glm::vec2 uv;
			uv.x = vertex.TextureCoordinate.X;
			uv.y = vertex.TextureCoordinate.Y;
			temp_uvs.push_back(uv);

			glm::vec3 normal;
			normal.x = vertex.Normal.X;
			normal.y = vertex.Normal.Y;
			normal.z = vertex.Normal.Z;
			
		}

		for (const auto& index : mesh.Indices)
		{
			temp_indices.push_back(index);
		}
	}

	m_totalIndices = temp_indices.size();

	for (const auto& index : temp_indices)
	{
		// Add position data
		glm::vec3 position;
		position.x = MyLoader.LoadedVertices[index].Position.X;
		position.y = MyLoader.LoadedVertices[index].Position.Y;
		position.z = MyLoader.LoadedVertices[index].Position.Z;
		out_vertices.push_back(position);
		// Add uv data
		glm::vec2 uv;
		uv.x = MyLoader.LoadedVertices[index].TextureCoordinate.X;
		uv.y = MyLoader.LoadedVertices[index].TextureCoordinate.Y;
		out_uvs.push_back(uv);
		// add normal data
		glm::vec3 normal;
		normal.x = MyLoader.LoadedVertices[index].Normal.X;
		normal.y = MyLoader.LoadedVertices[index].Normal.Y;
		normal.z = MyLoader.LoadedVertices[index].Normal.Z;
		out_normals.push_back(normal);
	}

	// Normalize Positions
	NormalizePositions(out_vertices);

	return true;
}

void Model::NormalizePositions(std::vector<glm::vec3> &out_vertices)
{
	float l_largest = 0.0f;
	for (int i = 0; i < out_vertices.size(); i++)
	{
		float t_length = sqrt((out_vertices[i].x * out_vertices[i].x) +
			(out_vertices[i].y * out_vertices[i].y) +
			(out_vertices[i].z * out_vertices[i].z));

		if (t_length > l_largest) 
			l_largest = t_length;
	}//for

	//printf("Normalizing model size by factor %f\n", l_largest);
	for (int i = 0; i < out_vertices.size(); i++)
	{
		out_vertices[i].x = out_vertices[i].x / l_largest;
		out_vertices[i].y = out_vertices[i].y / l_largest;
		out_vertices[i].z = out_vertices[i].z / l_largest;
	}//for
}