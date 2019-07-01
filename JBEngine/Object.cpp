#include "pch.h"
#include "Object.h"
#include "Camera.h"

Object::Object()
{
	m_model = new Model();
	m_shader = new Shader("Shaders/SimpleVert.vert", 
		"Shaders/SimpleFrag.frag");
	m_modelMatrix = glm::mat4();
	
}

Object::Object(const char * _modelFilePath)
{
	m_model = new Model(_modelFilePath);
	m_shader = new Shader("Shaders/SimpleVert.vert",
		"Shaders/SimpleFrag.frag");
	m_modelMatrix = glm::mat4();
}

Object::Object(const char * _modelFilePath, TextureType _textureType, const char * _textureFilePath)
{
	m_model = new Model(_modelFilePath);
	m_shader = new Shader("Shaders/TexturedVert.vert",
		"Shaders/TexturedFrag.frag");
	m_modelMatrix = glm::mat4();
	m_texture = new Texture(_textureType, _textureFilePath);
}


Object::~Object()
{
	// Clean up model
	delete m_model;
	// Clean up shader
	delete m_shader;
	// Clean up texture
	delete m_texture;
	// Clean up height map texture
	delete m_heightMap;
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

	// Send our transformation to the shader
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);


	if (m_texture)
	{
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetData());
		// Set TextureSampler sampler to use Texture Unit 0
		glUniform1i(m_shader->GetTextureSamplerID(), 0);
	}
	

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
	

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetNormalBuffer());
	glVertexAttribPointer(
		2,                  // attribute 2. must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
 	glDrawArrays(GL_TRIANGLES, 0, m_model->GetIndicesCount());

	// Check for any errors
	//GLenum err = glGetError();
	//int count = 0;
	//while (err != GL_NO_ERROR)
	//{
	//	std::cout << count++ << ": 0x" << std::hex << err << std::endl;
	//	err = glGetError();
	//}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}