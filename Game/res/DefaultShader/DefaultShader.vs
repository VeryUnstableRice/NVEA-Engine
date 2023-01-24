#version 330
layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoords;
layout(location=2) in vec3 normal;

out vec2 out_texcoord;
out vec4 out_color;
out vec3 out_normal;
out vec4 out_fragpos;
out mat4 out_view;
//out vec3 out_dirLight;


uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform vec4 color;

void main()
{
	out_fragpos = ProjectionMatrix*ViewMatrix*ModelMatrix*vec4(position, 1.0);

	out_texcoord = texCoords;
	out_color = color;
	out_view = ViewMatrix;

	out_normal = normalize(normal*mat3(ModelMatrix));
	gl_Position = out_fragpos;
}