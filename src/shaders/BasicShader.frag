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

struct DirectLight {
	vec3 direction;
	vec3 lightColor;

    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
};

struct LightProp {
    vec3 position;
	vec3 direction;
	vec3 lightColor;

    float ambientStrength;
    float diffuseStrength;
    float specularStrength;

	int lightType;
};

uniform MaterialProp material;
uniform LightProp light; 

uniform sampler2D Texture0;
uniform vec3 viewPos;

vec3 CalcDirLight(DirectLight light, vec3 normal, vec3 viewDirection){
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient  = light.ambientStrength * light.lightColor  * material.ambientColor;
    vec3 diffuse  = light.diffuseStrength * light.lightColor  * diff * material.diffuseColor;
    vec3 specular = light.specularStrength * light.lightColor * spec * material.specularColor;

    return (ambient + diffuse + specular);
}

void main()
{
	// ambient
    vec3 ambient = light.lightColor * light.ambientStrength * material.ambientColor;

	// diffuse 
	vec3 normalVec = normalize(normal);
	vec3 lightDir;
	switch(light.lightType){
		case 0:
			lightDir = normalize(-light.direction);
			break;
		case 1:
			lightDir = normalize(light.position - fragPos);
			break;
		default:
			break;
	}
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