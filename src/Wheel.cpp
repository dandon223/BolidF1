#include "Wheel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Wheel::Wheel(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat radius = 5, GLint numOfSides = 10) :
	basicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag"),
	wheelModel(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)),
	_x(x), _y(y), _z(z), _radius(radius), _numOfSides(numOfSides) {

	createCircle();
	makeTire(1);

	part1 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part2 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part3 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));


	part1->set_geometry(this->vertices, this->indicesCir);
	//check if possible to copy after this line ^
	part2->set_geometry(this->vertices2, this->indicesCir);

	part3->set_geometry(this->verticesTire,this->indicesTire);





	wheelModel.add(part1);
	wheelModel.add(part2);
	wheelModel.add(part3);
	wheelModel.bind_buffers();

}

Wheel::~Wheel() {
	wheelModel.free_buffers();
}

void Wheel::draw(glm::mat4& m) {
	wheelModel.draw(m);
}
void Wheel::translate(const glm::vec3& translateVector) {
	this->wheelModel.translate(translateVector);
}
void Wheel::rotate(float angle, const glm::vec3& rotationAxis) {
	wheelModel.rotate(angle, rotationAxis);
}
void Wheel::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	wheelModel.rotate(angle, rotationAxis, fixedPoint);
}
void Wheel::scale(const glm::vec3& scaleVector) {
	wheelModel.scale(scaleVector);
}
void Wheel::setProjectionView(glm::mat4 p, glm::mat4 v) {
	GLint projLoc = glGetUniformLocation(basicShader.get_programID(), "projection");
	// setup view matrix - get it from camera object
	GLint viewLoc = glGetUniformLocation(basicShader.get_programID(), "view");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(box1.model_));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(p));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(v));
}
void Wheel::shaderUse() {
	basicShader.Use();
}


void Wheel::createCircle()
{
	GLfloat doublePi = 2.0f * 3.14159265358979323846;

	/*std::vector<GLfloat> vertices = { _x, _y, _z, 0.01f, 0.01f };
	std::vector<GLuint> indices;*/

	for (int i = 0; i < _numOfSides; i++) {
		vertices.push_back(_x + (_radius * cos(i * doublePi / _numOfSides)));
		vertices.push_back(_y + (_radius * sin(i * doublePi / _numOfSides)));
		vertices.push_back(_z);
		vertices.push_back(0.01f);
		vertices.push_back(0.01f);

		indicesCir.push_back(0);
		if (i == _numOfSides - 1) {
			indicesCir.push_back(1);
		}
		else {
			indicesCir.push_back(i + 2);
		}
		indicesCir.push_back(i + 1);
	}

}

void Wheel::makeTire(GLfloat width)
{
	vertices2 = vertices;
	for (int i = 0; i < vertices.size()/5; ++i) {
		vertices2[5 * i + 2] += width;
	}

	GLint verticesSize = vertices.size()/5 -1;

	for (int i = 0; i < verticesSize; ++i) {
		indicesTire.push_back(i);
		indicesTire.push_back(((i + 1) % verticesSize) + verticesSize);
		indicesTire.push_back(i + verticesSize);
		
		indicesTire.push_back((i + 1) % verticesSize);
		indicesTire.push_back(((i + 1) % verticesSize) + verticesSize);
		indicesTire.push_back(i);
	}
	verticesTire.insert(verticesTire.end(), vertices.begin() + 5, vertices.end());
	verticesTire.insert(verticesTire.end(), vertices2.begin() + 5, vertices2.end());
}





