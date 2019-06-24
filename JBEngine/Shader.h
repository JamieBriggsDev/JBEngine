#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

class Shader
{
private:
	// Program ID
	GLuint m_programID;
	// Matrix ID
	GLuint m_matrixID;
	// Texture Sampler ID
	GLuint m_texSamplerID;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	int OpenVertexShader(const char* vertex_file_path);
	int OpenFragmentShader(const char* fragment_file_path);
public:
	Shader(const char* vertex_file_path, const char * fragment_file_path);
	~Shader();
	int GetProgramID(){ return m_programID; }
};

