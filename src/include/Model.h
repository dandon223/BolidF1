#ifndef MODEL_H
#define MODEL_H

#include "Object3D.h"
class Model : public BasicObject {
private:
	std::vector<BasicObject*> objectsVector_;
	//std::vector<std::unique_ptr<BasicObject>> objectsVector_;
public:
	Model(const glm::vec3&, const glm::vec3&);
	virtual ~Model();

	bool add(BasicObject*);
	bool remove(unsigned int);
	std::unique_ptr<BasicObject*> getChild(unsigned int);

	virtual void bind_buffers();
	virtual void free_buffers();
	virtual void draw();

	//virtual void set_centerPoint(const glm::vec3&);
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
