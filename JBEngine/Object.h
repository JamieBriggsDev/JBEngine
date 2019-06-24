#pragma once

#include <GL/glew.h>
#include <glm.hpp>

#include "Model.h"
#include "Shader.h"

class Camera;

class Object
{
private:
	Model* m_model;
	Shader* m_shader;
	glm::mat4 m_modelMatrix;
public:
	Object();
	~Object();
	// Get functions
	Model* GetModel() { return m_model; }
	Shader* GetShader() { return m_shader; }
	glm::mat4 GetModelMatrix() { return m_modelMatrix; }
	// Set function
	void SetModelMatrix(glm::mat4 _modelMatrix);
	// Draw function
	void Draw(Camera _camera);
};

