#version 330 core
in vec3 vecColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture0;
uniform vec3 lightColor;

void main()
{
   color = vec4(lightColor, 1.0f) * texture(Texture0, TexCoord);
}