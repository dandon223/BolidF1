#ifndef OBJECT3D_H
#define OBJECT3D_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include "include/shprogram.h"

struct Vertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat xColor;
	GLfloat yColor;
	GLfloat zColor;
	GLfloat xTex;
	GLfloat yTex;

	Vertex(GLfloat x_ = 0.0f, GLfloat y_ = 0.0f, GLfloat z_ = 0.0f, GLfloat xColor_ = 0.0f, 
		   GLfloat yColor_ = 0.0f, GLfloat zColor_ = 0.0f, 
		   GLfloat xTex_ = 0.0f, GLfloat yTex_ = 0.0f) : x(x_), y(y_), z(z_), xColor(xColor_), yColor(yColor_), zColor(zColor_), xTex(xTex_), yTex(yTex_) {}
};
class BasicObject {
public:
	virtual ~BasicObject() {}
	virtual void bind_buffers() = 0;
	virtual void free_buffers() = 0;
	virtual void draw() = 0;

	//virtual void set_centerPoint(const glm::vec3&) = 0;
	virtual void translate(const glm::vec3&) = 0;
	virtual void rotate(float, const glm::vec3&) = 0;
	virtual void rotate(float, const glm::vec3&, const glm::vec3&) = 0;
	virtual void scale(const glm::vec3&) = 0;
	//virtual void change_color(const glm::vec3&) = 0;
};

class Object3D : public BasicObject {
private:
	GLuint VAO, VBO, EBO;
	
protected:
	ShaderProgram* shader_;

public:
	glm::vec3 centerPoint_;
	glm::mat4 model_;
	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;

	Object3D();
	virtual ~Object3D();
	virtual void bind_buffers();
	virtual void free_buffers();
	virtual void draw();

	//virtual void set_centerPoint(const glm::vec3&);
	virtual void translate(const glm::vec3&);
	virtual void rotate(float, const glm::vec3&);
	virtual void rotate(float, const glm::vec3&, const glm::vec3&);
	virtual void scale(const glm::vec3&);
	//virtual void change_color(const glm::vec3&);
};

class Model : public BasicObject {
private:
	glm::vec3 centerPoint_;
	std::vector<BasicObject *> objectsVector_;

public:
	Model();
	virtual ~Model();

	bool add(BasicObject *);
	bool remove(unsigned int);
	std::unique_ptr<BasicObject *> getChild(unsigned int);

	virtual void bind_buffers();
	virtual void free_buffers();
	virtual void draw();

	//virtual void set_centerPoint(const glm::vec3&);
	virtual void translate(const glm::vec3&);
	virtual void rotate(float, const glm::vec3&);
	virtual void rotate(float, const glm::vec3&, const glm::vec3&);
	virtual void scale(const glm::vec3&);
	//virtual void change_color(const glm::vec3&);
};

class Cube : public Object3D {
public:

	Cube(const ShaderProgram* );
	~Cube();
};

#endif // !OBJECT3D_H

