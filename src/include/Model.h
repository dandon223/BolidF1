#ifndef MODEL_H
#define MODEL_H

#include "Object3D.h"
class Model : public BasicObject {
private:
	std::vector<BasicObject*> objectsVector_;
	/*mod*/
	glm::mat4 model_;
	glm::mat4 rotationMatrix_;
	/*end mod*/
public:

	Model(const glm::vec3&, const glm::vec3&);
	virtual ~Model();

	bool add(BasicObject*);
	bool remove(unsigned int);
	std::unique_ptr<BasicObject*> getChild(unsigned int);

	virtual void bind_buffers();
	virtual void free_buffers();
	virtual void draw(glm::mat4& = glm::mat4());

	virtual void translate(const glm::vec3&);
	virtual void rotate(float, const glm::vec3&);
	virtual void rotate(float, const glm::vec3&, const glm::vec3&);
	virtual void scale(const glm::vec3&);
};

class Cube : public Object3D {
public:

	Cube(const ShaderProgram*);
	~Cube();
};

#endif
