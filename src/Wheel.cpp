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

	std::vector<GLfloat> vertices;
	vertices.push_back()



}





