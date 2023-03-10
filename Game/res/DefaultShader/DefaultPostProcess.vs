#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
uniform mat4 viewmatrix;
out vec2 texCoord;

void main()
{
    gl_Position = viewmatrix*vec4(position, 1.0); 
	texCoord = texcoord;
}  