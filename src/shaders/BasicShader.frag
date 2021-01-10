#version 330 core
out vec4 color;

in vec3 fragPos;
in vec3 normal;
in vec2 TexCoord;

uniform sampler2D Texture0;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	// ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	// diffuse 
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse);
	color = vec4(result, 1.0f);//*texture(Texture0, TexCoord);
	//*texture(Texture0, TexCoord) ;
}