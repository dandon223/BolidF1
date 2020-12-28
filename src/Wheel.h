#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <math.h>

#include "include/shprogram.h"
#include "include/Model.h"

class Wheel {
private:

	GLint _numOfSides;
	GLfloat _x, _y, _z, _radius;

	std::vector<GLfloat> vertices = { _x, _y, _z, 0.01f, 0.01f }, vertices2, verticesTire;
	std::vector<GLuint> indicesCir, indicesTire;

	ShaderProgram basicShader;
	Model wheelModel;
	Object3D* part1;
	Object3D* part2;
	Object3D* part3;
public:
	Wheel(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numOfSides);
	virtual ~Wheel();
	virtual void draw(glm::mat4 & = glm::mat4());

	void translate(const glm::vec3&);
	void rotate(float, const glm::vec3&);
	void rotate(float, const glm::vec3&, const glm::vec3&);
	void scale(const glm::vec3&);
	void setProjectionView(glm::mat4 p, glm::mat4 w);
	void shaderUse();

	void createCircle();
	void makeTire(GLfloat width);
	

};