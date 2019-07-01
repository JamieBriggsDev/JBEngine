#version 430 core

// UV data passed from vertex shader.
in vec2 UV;

// Ouput data
out vec3 color;

// Texture Sampler
uniform sampler2D TextureSampler;

void main(){

	// Output color = texture
    color = texture( TextureSampler, UV ).rgb;
} 