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
	GLfloat _radius, _width;

	std::vector<GLfloat> vertices = { 0.f, 0.f, 0.f, 0.5f, 0.5f }, vertices2, verticesTire;
	std::vector<GLuint> indicesCir, indicesTire;

	ShaderProgram *basicShader;
	Object3D* opona[3];

public:
	Kolo(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram *basicShader, GLfloat radius, GLint numOfSides, GLfloat width, GLchar side, GLchar direction);

	void createCircle();
	void makeTire();

};

class Zawieszenie : public Model {
private:

	GLfloat _width;

	std::vector<GLfloat> verticesBeam = {
		0.0f, 0.0f, 0.0f,	0.5f, 0.1f,	//0
		0.02f, 0.0f, 0.0f,	0.5f, 0.1f,	//1
		0.02f, 0.02f, 0.0f,	0.5f, 0.1f,	//2
		0.0f, 0.02f, 0.0f,	0.5f, 0.1f	//3
	};

	std::vector<GLfloat> verticesBeam2, verticesBeamCon;
	std::vector<GLuint> indicesBeam, indicesSquare = { 0 ,1 , 2, 0, 2, 3 };

	ShaderProgram* basicShader;

	Object3D* tylnaBelkaStabilizatora[12];
	Object3D* przedniaBelkaStabilizatora[12];

public:
	Zawieszenie(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram* basicShader);

	void makeBeam();

};