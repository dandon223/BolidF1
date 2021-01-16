#ifndef LIGHT_H
#define LIGHT_H

#include "Object3D.h"

/*Obiekt reprezentuj¹cy œwiat³o, umo¿liwia umieszczenie obiektu œwiat³a w scenie*/

class LightSource : public Object3D {
public:
	glm::vec3 ambientStrength_;
	glm::vec3 diffuseStrength_;
	glm::vec3 specularStrength_;

	LightSource(
		const glm::vec3& = glm::vec3(), 
		const glm::vec3& = glm::vec3(0.1, 0.1, 0.1), 
		const glm::vec3& = glm::vec3(0.5, 0.5, 0.5), 
		const glm::vec3& = glm::vec3(1.0, 1.0, 1.0), 
		const ShaderProgram* = nullptr);

	virtual void bind_buffers();
	virtual void draw(glm::mat4& = glm::mat4());
	virtual void set_geometry(const std::vector<GLfloat>&, const std::vector<GLuint>&);
};

#endif // !LIGHT_H
