#version 330
out vec4 color_output;

in vec2 out_texcoord;
in vec4 out_color;
in vec3 out_normal;
in mat4 out_view;
 
uniform sampler2D texture0;

uniform vec3 lightDirection;

uniform int doesHaveTexture;

void main()
{
	//if(color_output.w <=0.1) discard;
	if(doesHaveTexture != 0)
		color_output = texture2D(texture0, out_texcoord)*out_color;
	else
		color_output = out_color;
	
}
