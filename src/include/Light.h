#ifndef LIGHT_H
#define LIGHT_H

#include "Object3D.h"

/*Obiekt reprezentuj¹cy œwiat³o, umo¿liwia umieszczenie obiektu œwiat³a w scenie*/

class LightSource : public Object3D {
public:
	glm::vec3 lightColor_;
	float ambientStrength_;
	float diffuseStrength_;
	float specularStrength_;

	LightSource(
		const glm::vec3 & = glm::vec3(),
		const glm::vec3 & = glm::vec3(1.0, 1.0, 1.0),
		const float = 0.1,
		const float = 1.0,
		const float = 0.5, 
		const ShaderProgram* = nullptr);

	virtual void bind_buffers();
	virtual void draw(glm::mat4& = glm::mat4());
	virtual void set_geometry(const std::vector<GLfloat>&, const std::vector<GLuint>&);
	void pass_parameters_to_shader(ShaderProgram*);
};

#endif // !LIGHT_H
