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

/*ToDo
0) Konstruktory argumentowe
1) Zaimplementuj pozostale metody
2) Popraw wskazniki na smart_ptr
3) wyczyœæ kod*/
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
};

class Object3D : public BasicObject {
private:
	GLuint VAO, VBO, EBO;
	glm::mat4 model_;
	
protected:
	ShaderProgram* shader_;
	std::string texturePath_;

public:
	glm::vec3 centerPoint_;
	glm::vec3 translateVector_;
	glm::vec3 scaleVector_;
	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;

	Object3D();
	Object3D(const glm::vec3&, const glm::vec3&, ShaderProgram*);
	virtual ~Object3D();
	virtual void bind_buffers();
	virtual void free_buffers();
	virtual void draw();

	//virtual void set_centerPoint(const glm::vec3&);
	virtual void translate(const glm::vec3&);
	virtual void rotate(float, const glm::vec3&);
	virtual void rotate(float, const glm::vec3&, const glm::vec3&);
	virtual void scale(const glm::vec3&);

	void set_vertices(const std::vector<GLfloat>&);
	void set_indices(const std::vector<GLuint>&);
	void set_color(const glm::vec3&);
	bool set_shader(ShaderProgram*);
	bool set_texture(std::string);
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
};

class Cube : public Object3D {
public:

	Cube(const ShaderProgram* );
	~Cube();
};

#endif // !OBJECT3D_H

