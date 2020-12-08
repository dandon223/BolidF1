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

class TylnySpoiler {
private:
	std::vector<GLfloat> vertices = {
0.0f, -0.6f, 0.0f,		0.5f,  0.0f,// 0
0.3f, -0.2f, 0.0f,		1.0f,  0.3f,// 1
-0.3f, -0.2f, 0.0f,		0.03f,  0.3f,// 2
0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3
-0.3f, 0.6f, 0.0f,		0.03f,  1.0f,// 4
	};
	std::vector<GLuint> indices = {
		0, 1, 2,
		1, 3, 2,
		2, 3, 4,
	};
	std::vector<GLfloat> vertices1 = {
		 0.0f, -0.6f, -0.01f,		0.5f,  0.0f,// 0
		 0.3f, -0.2f, -0.01f,		1.0f,  0.2f,// 1
		 -0.3f, -0.2f, -0.01f,	0.0f,  0.2f,// 2
		0.3f, 0.6f, -0.01f,		1.0f,  1.0f,// 3
		-0.3f, 0.6f, -0.01f,		0.0f,  1.0f,// 4

		0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
		0.3f, -0.2f, 0.01f,		1.0f,  0.2f,// 6
		-0.3f, -0.2f, 0.01f,	0.0f,  0.2f,// 7
		0.3f, 0.6f, 0.01f,		1.0f,  1.0f,// 8
		-0.3f, 0.6f, 0.01f,		0.0f,  1.0f,// 9
	};
	std::vector<GLuint> indices1 = {
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
	std::vector<GLfloat> vertices2 = {
		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		0.8f, -0.01f , -0.2f,		0.0f,1.0f,	//1
		0.8f,0.01f, -0.2f,		1.0f, 1.0f, //2
		-0.8f,0.01f, -0.2f,		0.0f,1.0f,	//3
		-0.8f, -0.01f, 0.2f,		1.0f,0.0f,	//4
		0.8f, -0.01f , 0.2f,		1.0f,1.0f,	//5
		0.8f,0.01f, 0.2f,		1.0f, 0.0f, //6
		-0.8f,0.01f, 0.2f,		0.0f,0.0f,	//7

	};
	std::vector<GLuint> indices2 = {
		0,1,2,
		0,2,3,
		1,5,6,
		1,6,2,
		0,4,7,
		0,7,3,
		4,5,6,
		4,6,7,
		0,1,5,
		0,5,4,
		3,2,6,
		3,6,7,
	};
	std::vector<GLfloat> vertices3 = {
		-0.22f, -0.5f, -0.01f,		0.0f,0.0f,	//0
		-0.20f, -0.5f , -0.01f,	0.0f, 1.0f, //1
		-0.20f, -0.5f , 0.01f,  1.0f, 1.0f, //2
		-0.22f, -0.5f, 0.01f,	1.0f, 0.0f, //3
		0.20f,0.5f, -0.01f,		1.0f, 0.0f,	//4
		0.22f,0.5f, -0.01f,		0.0f, 0.0f, //5
		0.22f, 0.5f, 0.01f,	0.0f,1.0f,	//6
		0.20f, 0.5f, 0.01f,		1.0f, 1.0f,	//7

	};
	std::vector<GLuint> indices3 = {
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
	ShaderProgram basicShader;
	Model spoilerModel;
	Object3D *part1;
	Object3D *part12;
	Object3D *part2;
	Object3D *part22;
	Object3D *wing1;
	Object3D *wing2;
	Object3D *part3;
	Object3D *part4;
public:
	glm::vec3 centerPoint_;
	glm::vec3 scaleVector_;

	TylnySpoiler();
	virtual ~TylnySpoiler();
	virtual void draw(glm::mat4& = glm::mat4());

	void translate(const glm::vec3&);
	void rotate(float, const glm::vec3&);
	void rotate(float, const glm::vec3&, const glm::vec3&);
	void scale(const glm::vec3&);
};
