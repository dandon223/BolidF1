#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D Texture;

void main()
{
	color = texture(Texture, TexCoord) * vec4(0.5, 0.5, 0.5 , 1.0);
}
