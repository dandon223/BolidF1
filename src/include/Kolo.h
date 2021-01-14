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

class Kolo : public Model {
private:

	GLint _numOfSides;
	GLfloat _radius;
	GLfloat _width;

	std::vector<GLfloat> vertices = { 0.f, 0.f, 0.f, 0.5f, 0.5f }, vertices2, verticesTire;
	std::vector<GLuint> indicesCir, indicesTire;

	ShaderProgram *basicShader;
	Object3D* tylnaOs[6];
	Object3D* tylnaBelkaStabilizatora[6];

	Object3D* przedniaOs[6];
	Object3D* przedniaBelkaStabilizatora[6];

public:
	Kolo(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram *basicShader, GLfloat radius, GLint numOfSides, GLfloat width);

	void createCircle();
	void makeTire();

};