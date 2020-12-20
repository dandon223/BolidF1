#include "Wheel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Wheel::Wheel(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numOfSides) :
	basicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag"),
	WheelModel(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)),
	_x(x), _y(y), _z(z), _radius(radius),_numOfSides(numOfSides){}

std::vector<GLfloat> Wheel::createCircle()
{
	GLfloat doublePi = 2.0f * 3.14159265358979323846;

	std::vector<GLfloat> vertices = { _x, _y, _z, 0.01f, 0.01f };
	std::vector<GLuint> indices;

	for (int i = 0; i < _numOfSides; i++) {
		vertices.push_back(_x + (_radius * cos(i * doublePi / _numOfSides)));
		vertices.push_back(_y + (_radius * sin(i * doublePi / _numOfSides)));
		vertices.push_back(_z);
		vertices.push_back(0.01f);
		vertices.push_back(0.01f);

		indices.push_back(0);
		if (i == _numOfSides - 1) {
			indices.push_back(1);
		}
		else {
			indices.push_back(i + 2);
		}
		indices.push_back(i + 1);
	}



}





