#version 430 core

// Input vertex data
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec2 UV;

uniform mat4 MVP;

uniform sampler2D HeightSampler;

void main()
{
	// UV to be used in frag
	UV = vertexUV;

	// Height of heightmap
	float heightMapHeight = texture(HeightSampler, vertexUV).r;
	// Find new position
	vec3 newPosition = vertexPosition_modelspace + 
			(vertexNormal_modelspace * heightMapHeight);


	// Set gl_Position
	gl_Position =  MVP * vec4(newPosition,1);
	
}

