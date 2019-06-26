#include "pch.h"
#include "Object.h"
#include "Camera.h"

Object::Object()
{
	m_model = new Model();
	m_shader = new Shader("SimpleVert.vert", 
		"SimpleFrag.frag");
	m_modelMatrix = glm::mat4();
	m_texture = new Texture(TextureType::BMP, "Resources/Textures/image.bmp");
	
}

Object::Object(const char * _modelFilePath)
{
	m_model = new Model(_modelFilePath);
	m_shader = new Shader("SimpleVert.vert",
		"SimpleFrag.frag");
	m_modelMatrix = glm::mat4();
	m_texture = new Texture(TextureType::BMP, "Resources/Textures/image.bmp");

}

Object::~Object()
{
	// Clean up model
	delete m_model;
	// Clean up shader
	delete m_shader;
	// Clean up texture
	delete m_texture;
}

// Set model matrix
void Object::SetModelMatrix(glm::mat4 _modelMatrix) 
{ 
	m_modelMatrix = _modelMatrix; 
}

// Draw function
void Object::Draw(Camera* _camera)
{
	// MVP
	glm::mat4 MVP = _camera->GetProjectionView() * m_modelMatrix;

	// Use shader
	glUseProgram(m_shader->GetProgramID());

	// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetData());
	// Set our "TextureSampler" sampler to use Texture Unit 0
	glUniform1i(m_textureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetVertexBuffer());
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UV
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetUVBuffer());
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}