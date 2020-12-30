#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include "include/shprogram.h"
#include "include/Model.h"

class PrzedniSpoiler :public Model {
private:
	std::vector<GLfloat> vertices = {
		-0.5f, -0.01f, -0.1f,	0.01f,  0.01f,// 0
		0.5f, -0.01f, -0.1f,	1.0f,  0.01f,// 1
		0.5f, 0.01f, -0.1f,		1.0f,  0.1f,// 2
		-0.5f, 0.01f, -0.1f,	0.01f,  0.1f,// 3
		-0.5f, -0.01f, 0.1f,	0.01f,  0.01f,// 4
		0.5f, -0.01f, 0.1f,		0.01f,  0.01f,// 5
		0.5f, 0.01f, 0.1f,		1.0f,  0.5f,// 6
		-0.5f, 0.01f, 0.1f,		0.01f,  0.5f,// 7
	};
	std::vector<GLuint> indices = {
		0, 1, 2,
		0, 2, 3,
		1,5,6,
		1,6,2,
		0,1,5,
		0,5,4,
		0,4,7,
		0,7,3,
		3,2,6,
		3,6,7,
		5,4,6,
		6,4,7,
	};
	std::vector<GLfloat> vertices1 = {
		 -0.5f, -0.2f, 0.01f,		0.0f,  0.1f,// 0
		 0.5f, -0.2f,  0.01f,		1.0f,  0.1f,// 1
		 0.5f, 0.2f,   0.01f,		1.0f,  1.0f,// 2
		0.4f, 0.2f,    0.01f,		0.9f,  1.0f,// 3
		0.2f, 0.0f,    0.01f,		0.7f,  0.55f,// 4
		-0.2f, 0.0f, 0.01f,			0.3f,  0.55f,// 5
		-0.4f, 0.2f, 0.01f,			0.1f,  1.0f,// 6
		-0.5f, 0.2f, 0.01f,			0.0f,  1.0f,// 7

		 -0.5f, -0.2f, -0.01f,		0.0f,  0.0f,// 8
		 0.5f, -0.2f,  -0.01f,		1.0f,  0.0f,// 9
		 0.5f, 0.2f,   -0.01f,		0.0f,  0.2f,// 10
		0.4f, 0.2f,    -0.01f,		1.0f,  1.0f,// 11
		0.2f, 0.0f,    -0.01f,		0.0f,  1.0f,// 12
		-0.2f, 0.0f,-0.01f,			0.5f,  0.0f,// 13
		-0.4f, 0.2f, -0.01f,		1.0f,  0.2f,// 14
		-0.5f, 0.2f, -0.01f,		0.0f,  0.2f,// 15
	};
	std::vector<GLuint> indices1 = {
		0,6,7,
		0,5,6,
		0,1,5,
		1,4,5,
		1,3,4,
		1,2,3,
		1,9,10,
		1,10,2,
		8,0,7,
		8,7,15,
		7,6,14,
		7,14,15,
		6,5,13,
		6,13,14,
		5,4,12,
		5,12,13,
		4,3,11,
		4,11,12,
		3,2,10,
		3,10,11,
		9,11,10,
		9,12,11,
		9,8,12,
		8,13,12,
		8,14,13,
		8,15,14,
		0,9,1,
		0,8,9,
	};
	std::vector<GLfloat> vertices2 = {
		-0.4f, -0.2f, -0.01f,		0.0f,0.0f,	//0
		0.3f, -0.2f , -0.01f,		0.8f,0.0f,	//1
		0.4f,-0.1f, -0.01f,		1.0f, 0.3f, //2
		0.4f,0.0f, -0.01f,		1.0f,0.6f,	//3
		-0.4f,0.2f, -0.01f,		0.0f,1.0f,	//4

		-0.4f, -0.2f, 0.01f,		1.0f,0.0f,	//5
		0.3f, -0.2f , 0.01f,		0.2f,0.0f,	//6
		0.4f,-0.1f, 0.01f,		0.0f, 0.3f, //7
		0.4f,0.0f, 0.01f,		0.0f,0.6f,	//8
		-0.4f,0.2f, 0.01f,		1.0f,1.0f,	//9

	};
	std::vector<GLuint> indices2 = {
		0,1,4,
		1,4,3,
		1,2,3,
		0,5,1,
		5,6,1,
		1,6,2,
		6,7,2,
		2,7,3,
		7,8,3,
		3,8,9,
		3,9,4,
		4,5,0,
		9,5,4,
		6,8,7,
		5,9,6,
		8,9,6,
	};
	ShaderProgram *basicShader;
	Object3D *part1;
	Object3D *part2;
	Object3D *part3;
	Object3D *part4;
public:
	PrzedniSpoiler(const glm::vec3& centerPoint, const glm::vec3& scaleVector,ShaderProgram *basicShader);
};
