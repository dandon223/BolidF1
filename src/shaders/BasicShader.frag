#version 330 core
out vec4 color;

in vec3 fragPos;
in vec3 normal;
in vec2 TexCoord;

uniform sampler2D Texture0;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	// diffuse 
	vec3 normalVec = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(normalVec, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normalVec);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular);
	color = texture(Texture0, TexCoord)*vec4(result, 1.0f);
	//*texture(Texture0, TexCoord) ;
}