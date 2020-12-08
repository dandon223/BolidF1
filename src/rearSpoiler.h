#pragma once
#include "shprogram.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RearSpoiler {
private:
	const GLuint WIDTH = 800, HEIGHT = 600;

	float rotAngleX;
	float rotAngleY;
	float rotAngleZ;
	Camera &camera;

	glm::vec3 translateVector;
	glm::vec3 rotationPoint;

	GLuint Texture1_id;
	GLuint Texture2_id;
	ShaderProgram & Program;
	GLfloat vertices[25] = {
		0.0f, -0.6f, 0.0f,		0.5f,  0.0f,// 0
		0.3f, -0.2f, 0.0f,		1.0f,  0.2f,// 1
		-0.3f, -0.2f, 0.0f,		0.03f,  0.2f,// 2
		0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3
		-0.3f, 0.6f, 0.0f,		0.03f,  1.0f,// 4
	};
	GLuint indices[9] = {
		0, 1, 2,
		1, 3, 2,
		2, 3, 4,
	};
	GLfloat vertices1[50] = {
		 0.0f, -0.6f, 0.0f,		0.5f,  0.0f,// 0
		 0.3f, -0.2f, 0.0f,		1.0f,  0.2f,// 1
		 -0.3f, -0.2f, 0.0f,	0.0f,  0.2f,// 2
		0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3
		-0.3f, 0.6f, 0.0f,		0.0f,  1.0f,// 4

		0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
		0.3f, -0.2f, 0.01f,		1.0f,  0.2f,// 6
		-0.3f, -0.2f, 0.01f,	0.0f,  0.2f,// 7
		0.3f, 0.6f, 0.01f,		1.0f,  1.0f,// 8
		-0.3f, 0.6f, 0.01f,		0.0f,  1.0f,// 9
	};
	GLuint indices1[39] = {
		0,5,1,
		5,6,1,
		0,5,2,
		2,5,7,
		1,6,3,
		6,8,3,
		2,7,4,
		7,9,4,
		3,8,4,
		8,9,4,
		6,8,7,
		8,9,7,
		5,6,7,
	};
	GLfloat vertices2[30] = {
		0.5f, 0.1f, 0.0f,		1.0f,1.0f,	//0
		-0.98f, 0.1f , 0.0f,	0.0f,1.0f,	//1
		-0.98f,0.0f, -0.4f,		1.0f, 0.0f, //2
		0.5f,0.0f, -0.4f,		0.0f,0.0f,	//3
		0.5f, 0.15f, -0.3f,		0.0f,1.0f,	//4
		-0.98f, 0.15f, -0.3f,	0.0f,0.0f,	//5

	};
	GLuint indices2[24] = {
		0,3,4,
		1,2,5,
		0,3,1,
		3,2,1,
		1,0,4,
		1,4,5,
		2,3,4,
		2,4,5,
	};
	GLfloat vertices3[40] = {
		0.0f, -0.5f, 0.0f,		0.0f,0.0f,	//0
		0.02f, -0.5f , 0.0f,	0.0f, 1.0f, //1
		0.02f, -0.5f , -0.02f,  1.0f, 1.0f, //2
		0.0f, -0.5f, -0.02f,	1.0f, 0.0f, //3
		0.2f,0.5f, 0.0f,		1.0f, 0.0f,	//4
		0.24f,0.5f, 0.0f,		0.0f, 0.0f, //5
		0.24f, 0.5f, -0.02f,	0.0f,1.0f,	//6
		0.2f, 0.5f, -0.02f,		1.0f, 1.0f,	//7

	};
	GLuint indices3[36] = {
		0,1,2,
		0,2,3,
		1,2,6,
		1,6,5,
		0,1,5,
		0,5,4,
		3,0,4,
		3,4,7,
		3,2,6,
		3,6,7,
		4,5,6,
		4,6,7,
	};
	GLuint VBO[4];
	GLuint VAO[4];
	GLuint EBO[4];



public:
	RearSpoiler(const GLchar* image1Path, const GLchar* image2Path, ShaderProgram & shaderProgram , Camera &camera);
	void Draw();
	void SetProgram(ShaderProgram theProgram);
	glm::vec3 GetTransVector();
	void SetTransVector(glm::vec3 newTransVector);
	void SetRotPoint(glm::vec3 newRotPoint);
	glm::vec3 GetRotPoint();
	void SetRotationAngleX(float newAngleX);
	void SetRotationAngleY(float newAngleY);
	void SetRotationAngleZ(float newAngleZ);
};

