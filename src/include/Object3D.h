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

class Object3D {
public:
	glm::vec3 centerPoint;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	Object3D();
	~Object3D();
	void set_centerPoint(glm::vec3);
	void traslate(glm::vec3);
	void rotate(glm::vec3);
	void scale(float);
	void draw();
};

class cube : public Object3D {
public:

	cube();
	~cube();
};

#endif // !OBJECT3D_H

