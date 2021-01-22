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

class Kola : public Model {
private:

	GLint _numOfSides;
	GLfloat _radius;
	GLfloat _width;

	std::vector<GLfloat> verticesBeam = {
		0.0f, 0.0f, 0.0f,	0.5f, 0.1f,	//0
		0.02f, 0.0f, 0.0f,	0.5f, 0.1f,	//1
		0.02f, 0.02f, 0.0f,	0.5f, 0.1f,	//2
		0.0f, 0.02f, 0.0f,	0.5f, 0.1f	//3
	};

	std::vector<GLfloat> vertices = { 0.f, 0.f, 0.f, 0.5f, 0.5f }, vertices2, verticesTire, verticesBeam2, verticesBeamCon;
	std::vector<GLuint> indicesCir, indicesTire, indicesBeam, indicesSquare = { 0 ,1 , 2, 0, 2, 3 };

	ShaderProgram *basicShader;
	Object3D* tylnaOs[6];
	Object3D* tylnaBelkaStabilizatora[12];

	Object3D* przedniaOs[6];
	Object3D* przedniaBelkaStabilizatora[12];

public:
	Kola(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram *basicShader, GLfloat radius, GLint numOfSides, GLfloat width);

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