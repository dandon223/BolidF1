#ifndef LIGHT_H
#define LIGHT_H

#include "Object3D.h"

class LightSource : public Object3D {
public:
	glm::vec3 lightColor_;

	LightSource(const glm::vec3&, const glm::vec3&, const ShaderProgram*);
	virtual void bind_buffers();
	virtual void draw(glm::mat4& = glm::mat4());
};

#endif // !LIGHT_H
