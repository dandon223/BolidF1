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

class TylnySpoiler : public Model {
private:
	std::vector<GLfloat> vertices = {
	0.0f, -0.6f, 0.0f,		0.5f,  0.0f,// 0
	0.3f, -0.2f, 0.0f,		1.0f,  0.3f,// 1
	-0.3f, -0.2f, 0.0f,		0.03f,  0.3f,// 2

	-0.3f, -0.2f, 0.0f,		0.03f,  0.3f,// 2
	0.3f, -0.2f, 0.0f,		1.0f,  0.3f,// 1
	0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3

	-0.3f, -0.2f, 0.0f,		0.03f,  0.3f,// 2
	0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3
	-0.3f, 0.6f, 0.0f,		0.03f,  1.0f,// 4
	};
	std::vector<GLuint> indices = {
		0,1,2,3,4,5,6,7,8,
	};
	std::vector<GLfloat> vertices1 = {
		 0.0f, -0.6f, -0.01f,		0.5f,  0.0f,// 0
		 0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
		 0.3f, -0.2f, -0.01f,		1.0f,  0.2f,// 1

		 0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
		 0.3f, -0.2f, 0.01f,		1.0f,  0.2f,// 6
		 0.3f, -0.2f, -0.01f,		1.0f,  0.2f,// 1

		 0.0f, -0.6f, -0.01f,		0.5f,  0.0f,// 0
		 0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
		 -0.3f, -0.2f, -0.01f,		0.0f,  0.2f,// 2

		 -0.3f, -0.2f, -0.01f,		0.0f,  0.2f,// 2
		 0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
		 -0.3f, -0.2f, 0.01f,		0.0f,  0.2f,// 7

		 0.3f, -0.2f, -0.01f,		1.0f,  0.2f,// 1
		 0.3f, -0.2f, 0.01f,		1.0f,  0.2f,// 6
		0.3f, 0.6f, -0.01f,			1.0f,  1.0f,// 3

		0.3f, -0.2f, 0.01f,			1.0f,  0.2f,// 6
		0.3f, 0.6f, 0.01f,			1.0f,  1.0f,// 8
		0.3f, 0.6f, -0.01f,			1.0f,  1.0f,// 3

		-0.3f, -0.2f, -0.01f,		0.0f,  0.2f,// 2
		-0.3f, -0.2f, 0.01f,		0.0f,  0.2f,// 7
		-0.3f, 0.6f, -0.01f,		0.0f,  1.0f,// 4

		-0.3f, -0.2f, 0.01f,		0.0f,  0.2f,// 7
		-0.3f, 0.6f, 0.01f,			0.0f,  1.0f,// 9
		-0.3f, 0.6f, -0.01f,		0.0f,  1.0f,// 4

		0.3f, 0.6f, -0.01f,			1.0f,  1.0f,// 3
		0.3f, 0.6f, 0.01f,			1.0f,  1.0f,// 8
		-0.3f, 0.6f, -0.01f,		0.0f,  1.0f,// 4

		0.3f, 0.6f, 0.01f,			1.0f,  1.0f,// 8
		-0.3f, 0.6f, 0.01f,			0.0f,  1.0f,// 9
		-0.3f, 0.6f, -0.01f,		0.0f,  1.0f,// 4

		0.3f, -0.2f, 0.01f,			1.0f,  0.2f,// 6
		0.3f, 0.6f, 0.01f,			1.0f,  1.0f,// 8
		-0.3f, -0.2f, 0.01f,		0.0f,  0.2f,// 7

		0.3f, 0.6f, 0.01f,			1.0f,  1.0f,// 8
		-0.3f, 0.6f, 0.01f,			0.0f,  1.0f,// 9
		-0.3f, -0.2f, 0.01f,		0.0f,  0.2f,// 7

		0.0f, -0.6f, 0.01f,			0.5f,  0.0f,// 5
		0.3f, -0.2f, 0.01f,			1.0f,  0.2f,// 6
		-0.3f, -0.2f, 0.01f,		0.0f,  0.2f,// 7
		
		
	};
	std::vector<GLuint> indices1 = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
		33,34,35,36,37,38,
	};
	std::vector<GLfloat> vertices2 = {
		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		0.8f, -0.01f , -0.2f,		0.0f,1.0f,	//1
		0.8f,0.01f, -0.2f,			1.0f, 1.0f, //2

		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		0.8f,0.01f, -0.2f,			1.0f, 1.0f, //2
		-0.8f,0.01f, -0.2f,			0.0f,1.0f,	//3

		0.8f, -0.01f , -0.2f,		0.0f,1.0f,	//1
		0.8f, -0.01f , 0.2f,		1.0f,1.0f,	//5
		0.8f,0.01f, 0.2f,			1.0f, 0.0f, //6

		0.8f, -0.01f , -0.2f,		0.0f,1.0f,	//1
		0.8f,0.01f, 0.2f,			1.0f, 0.0f, //6
		0.8f,0.01f, -0.2f,			1.0f, 1.0f, //2

		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		-0.8f, -0.01f, 0.2f,		1.0f,0.0f,	//4
		-0.8f,0.01f, 0.2f,			0.0f,0.0f,	//7

		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		-0.8f,0.01f, 0.2f,			0.0f,0.0f,	//7
		-0.8f,0.01f, -0.2f,			0.0f,1.0f,	//3

		-0.8f, -0.01f, 0.2f,		1.0f,0.0f,	//4
		0.8f, -0.01f , 0.2f,		1.0f,1.0f,	//5
		0.8f,0.01f, 0.2f,			1.0f, 0.0f, //6
		
		-0.8f, -0.01f, 0.2f,		1.0f,0.0f,	//4
		0.8f,0.01f, 0.2f,			1.0f, 0.0f, //6
		-0.8f,0.01f, 0.2f,			0.0f,0.0f,	//7

		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		0.8f, -0.01f , -0.2f,		0.0f,1.0f,	//1
		0.8f, -0.01f , 0.2f,		1.0f,1.0f,	//5

		-0.8f, -0.01f, -0.2f,		0.0f,0.0f,	//0
		0.8f, -0.01f , 0.2f,		1.0f,1.0f,	//5
		-0.8f, -0.01f, 0.2f,		1.0f,0.0f,	//4

		-0.8f,0.01f, -0.2f,			0.0f,1.0f,	//3
		0.8f,0.01f, -0.2f,			1.0f, 1.0f, //2
		0.8f,0.01f, 0.2f,			1.0f, 0.0f, //6

		-0.8f,0.01f, -0.2f,			0.0f,1.0f,	//3
		0.8f,0.01f, 0.2f,			1.0f, 0.0f, //6
		-0.8f,0.01f, 0.2f,			0.0f,0.0f,	//7
	};
	std::vector<GLuint> indices2 = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
	};
	std::vector<GLfloat> vertices3 = {
		-0.22f, -0.5f, -0.01f,		0.0f,0.0f,	//0
		-0.20f, -0.5f , -0.01f,		0.0f, 1.0f, //1
		-0.20f, -0.5f , 0.01f,		1.0f, 1.0f, //2

		-0.22f, -0.5f, -0.01f,		0.0f,0.0f,	//0
		-0.20f, -0.5f , 0.01f,		1.0f, 1.0f, //2
		-0.22f, -0.5f, 0.01f,		1.0f, 0.0f, //3

		-0.20f, -0.5f , -0.01f,		0.0f, 1.0f, //1
		-0.20f, -0.5f , 0.01f,		1.0f, 1.0f, //2
		0.22f, 0.5f, 0.01f,			0.0f,1.0f,	//6

		-0.20f, -0.5f , -0.01f,		0.0f, 1.0f, //1
		0.22f, 0.5f, 0.01f,			0.0f,1.0f,	//6
		0.22f,0.5f, -0.01f,			0.0f, 0.0f, //5

		-0.22f, -0.5f, -0.01f,		0.0f,0.0f,	//0
		-0.20f, -0.5f , -0.01f,		0.0f, 1.0f, //1
		0.22f,0.5f, -0.01f,			0.0f, 0.0f, //5

		-0.22f, -0.5f, -0.01f,		0.0f,0.0f,	//0
		0.22f,0.5f, -0.01f,			0.0f, 0.0f, //5
		0.20f,0.5f, -0.01f,			1.0f, 0.0f,	//4
		
		-0.22f, -0.5f, 0.01f,		1.0f, 0.0f, //3
		-0.22f, -0.5f, -0.01f,		0.0f,0.0f,	//0
		0.20f,0.5f, -0.01f,			1.0f, 0.0f,	//4

		-0.22f, -0.5f, 0.01f,		1.0f, 0.0f, //3
		0.20f,0.5f, -0.01f,			1.0f, 0.0f,	//4
		0.20f, 0.5f, 0.01f,			1.0f, 1.0f,	//7

		-0.22f, -0.5f, 0.01f,		1.0f, 0.0f, //3
		-0.20f, -0.5f , 0.01f,		1.0f, 1.0f, //2
		0.22f, 0.5f, 0.01f,			0.0f,1.0f,	//6

		-0.22f, -0.5f, 0.01f,		1.0f, 0.0f, //3
		0.22f, 0.5f, 0.01f,			0.0f,1.0f,	//6
		0.20f, 0.5f, 0.01f,			1.0f, 1.0f,	//7

		0.20f,0.5f, -0.01f,			1.0f, 0.0f,	//4
		0.22f,0.5f, -0.01f,			0.0f, 0.0f, //5
		0.22f, 0.5f, 0.01f,			0.0f,1.0f,	//6

		0.20f,0.5f, -0.01f,			1.0f, 0.0f,	//4
		0.22f, 0.5f, 0.01f,			0.0f,1.0f,	//6
		0.20f, 0.5f, 0.01f,			1.0f, 1.0f,	//7
	};
	std::vector<GLuint> indices3 = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
	};
	ShaderProgram *basicShader;
	Object3D *part1;
	Object3D *part12;
	Object3D *part2;
	Object3D *part22;
	Object3D *wing1;
	Object3D *wing2;
	Object3D *part3;
	Object3D *part4;
public:
	TylnySpoiler(const glm::vec3& centerPoint, const glm::vec3& scaleVector,ShaderProgram *sp);
};
