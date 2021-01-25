#ifndef LIGHT_H
#define LIGHT_H

#include "Object3D.h"

class LightSource : public Object3D {
public:
	glm::vec3 lightColor_;
	float ambientStrength_;
	float diffuseStrength_;
	float specularStrength_;
	float constant_;
	float linear_;
	float quadratic_;

	LightSource(
		const glm::vec3 & = glm::vec3(),
		const glm::vec3 & = glm::vec3(1.0, 1.0, 1.0),
		const float = 0.1,
		const float = 1.0,
		const float = 0.5,
		const float = 1.0,
		const float = 0.001,
		const float = 0.0032,
		const ShaderProgram* = nullptr);

	virtual void bind_buffers();
	virtual void draw(glm::mat4& = glm::mat4());
	virtual void set_geometry(const std::vector<GLfloat>&, const std::vector<GLuint>&);
	void pass_parameters_to_shader(const ShaderProgram&, int);

private:
	std::string rights[8] = { "].position" , "].lightColor" , "].ambientStrength" , "].diffuseStrength" , "].specularStrength" ,
							  "].constant" , "].linear" , "].quadratic" };
};

class DirectLight : private Object3D {
public:
	DirectLight(
		const glm::vec3 & = glm::vec3(),
		const glm::vec3 & = glm::vec3(0.0, -1.0, 0.0),
		const glm::vec3 & = glm::vec3(1.0, 1.0, 1.0),
		const float = 0.2,
		const float = 0.5,
		const float = 1.0,
		const ShaderProgram* = nullptr);

	void pass_parameters_to_shader(const ShaderProgram&);

private:
	glm::vec3 direction_;
	glm::vec3 lightColor_;
	float ambientStrength_;
	float diffuseStrength_;
	float specularStrength_;
};

#endif // !LIGHT_H
