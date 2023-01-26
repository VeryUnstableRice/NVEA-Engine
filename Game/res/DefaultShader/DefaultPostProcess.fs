#version 330
out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D Screen;

void main()
{ 
    FragColor = texture(Screen, texCoord);
}