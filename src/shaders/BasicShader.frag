#version 330 core
out vec4 color;

in vec3 fragPos;
in vec3 normal;
in vec2 TexCoord;
 
uniform sampler2D Texture0;
uniform vec3 viewPos;

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

struct PointLight {
    vec3 position;
	vec3 lightColor;

	float constant;
	float linear;
	float quadratic;

    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
};

uniform MaterialProp material;
uniform PointLight PLight;

vec3 CalcDirectLight(DirectLight light, vec3 normal, vec3 viewDirection){
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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection){
	vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
    
    // combine results
    vec3 ambient  = light.ambientStrength * light.lightColor * material.ambientColor;
    vec3 diffuse  = light.diffuseStrength * light.lightColor * diff * material.diffuseColor;
    vec3 specular = light.specularStrength * light.lightColor * spec * material.specularColor;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    // properties
    vec3 normalVec = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = CalcPointLight(PLight, normalVec, fragPos, viewDir);

    // phase 1: Directional lighting
    //vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    //for(int i = 0; i < NR_POINT_LIGHTS; i++)
    //    result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);  

	color = texture(Texture0, TexCoord) * vec4(result, 1.0f);
}