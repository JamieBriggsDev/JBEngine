#include "pch.h"
#include "Object.h"
#include "Camera.h"

Object::Object()
{
	m_model = new Model();
	m_shader = new Shader("SimpleVertexShader.vert", 
		"SimpleFragmentShader.frag");
	m_modelMatrix = glm::mat4();
}


Object::~Object()
{
	// Clean up model
	delete m_model;
	// Clean up shader
	delete m_shader;
}

// Set model matrix
void Object::SetModelMatrix(glm::mat4 _modelMatrix) 
{ 
	m_modelMatrix = _modelMatrix; 
}

// Draw function
void Object::Draw(Camera _camera)
{

}