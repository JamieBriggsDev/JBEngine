#include "pch.h"
#include <objLoader.h>
#include <glm/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

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

Model::Model(const char * _filePath)
{
	LoadObj(_filePath, m_vertexBufferData, m_uvBufferData);

	//m_vertexBufferData.clear();
	//m_uvBufferData.clear();

	//// copy arrays into vectors
	//m_vertexBufferData.insert(m_vertexBufferData.end(),
	//	&g_cube_vertex_buffer_data[0],
	//	&g_cube_vertex_buffer_data[sizeof(g_cube_vertex_buffer_data)]);
	//m_uvBufferData.insert(m_uvBufferData.end(),
	//	&g_cube_uv_buffer_data[0],
	//	&g_cube_uv_buffer_data[sizeof(g_cube_uv_buffer_data)]);
	//m_vertexBufferData = g_cube_vertex_buffer_data;
	//m_uvBufferData = g_cube_uv_buffer_data;

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
	// Bind Vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, &m_vertexBufferData[0], GL_STATIC_DRAW);
	// Bind UV buffer
	glGenBuffers(1, &m_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvBufferSize, &m_uvBufferData[0], GL_STATIC_DRAW);
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



bool Model::LoadObj(const char * _filePath,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs)
{

	printf("Loading OBJ file %s...\n", _filePath);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(_filePath, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		//out_normals.push_back(normal);

	}
	fclose(file);

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