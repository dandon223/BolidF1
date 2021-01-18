#version 330 core
out vec4 color;

in vec3 fragPos;
in vec3 normal;
in vec2 TexCoord;

struct MaterialProp {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
}; 

struct LightProp {
    vec3 position;
	vec3 lightColor;

    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
};


uniform MaterialProp material;
uniform LightProp light; 

uniform sampler2D Texture0;
uniform vec3 viewPos;

void main()
{
	// ambient
    vec3 ambient = light.lightColor * light.ambientStrength * material.ambientColor;

	// diffuse 
	vec3 normalVec = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normalVec, lightDir), 0.0);
	vec3 diffuse = light.lightColor * light.diffuseStrength * (diff * material.diffuseColor);

	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normalVec);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.lightColor * light.specularStrength * (spec * material.specularColor);

	vec3 lightning = ambient + diffuse + specular;
	color = texture(Texture0, TexCoord) * vec4(lightning, 1.0f);
}