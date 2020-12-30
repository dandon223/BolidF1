#version 330 core
in vec3 vecColor;
in vec2 TexCoord;

out vec4 color;

uniform vec3 lightColor;
uniform sampler2D Texture0;

void main()
{
    color = vec4(lightColor, 1.0f) * texture(Texture0, TexCoord);
}