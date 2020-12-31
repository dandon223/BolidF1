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

class Kadlub :public Model{
private:
	std::vector<GLfloat> vertices = {
		-0.4f, 0.0f, -0.1f,		0.5f,  0.0f,// 0
		-0.4f, 0.2f, -0.1f,		0.4f,  0.0f,// 1
		-0.2f, 0.6f, -0.1f,		0.0f,  0.0f,// 2
		0.2f, 0.6f, -0.1f,		0.0f,  1.0f,// 3
		0.4f, 0.2f, -0.1f,		0.4f,  1.0f,// 4
		0.4f, 0.0f, -0.1f,		0.5f,  1.0f,// 5
		0.2f, -0.4f, -0.1f,		0.8f,  1.0f,// 6
		0.2f, -0.5f, -0.1f,		0.9f,  1.0f,// 7
		0.18f, -0.5f, -0.1f,		0.98f,  0.9f,// 8
		0.18f, -0.4f, -0.1f,		0.98f,  0.9f,// 9
		-0.18f, -0.4f, -0.1f,	0.96f,  0.0f,// 10
		-0.18f, -0.5f, -0.1f,	0.95f,  0.0f,// 11
		-0.2f, -0.5f, -0.1f,		0.9f,  0.0f,// 12
		-0.2f, -0.4f, -0.1f,		0.8f,  0.0f,// 13

		-0.4f, 0.0f, 0.1f,		0.5f,  0.27f,// 14
		-0.4f, 0.2f, 0.1f,		0.4f,  0.27f,// 15
		-0.2f, 0.6f, 0.1f,		0.0f,  0.27f,// 16
		0.2f, 0.6f, 0.1f,		0.0f,  0.75f,// 17
		0.4f, 0.2f, 0.1f,		0.4f,  0.75f,// 18
		0.4f, 0.0f, 0.1f,		0.5f,  0.75f,// 19
		0.2f, -0.4f, 0.1f,		0.8f,  0.745f,// 20
		0.2f, -0.5f, 0.1f,		0.9f,  0.745f,// 21
		0.18f, -0.5f, 0.1f,		0.98f,  0.9f,// 22
		0.18f, -0.4f, 0.1f,		0.98f,  0.9f,// 23
		-0.18f, -0.4f, 0.1f,	0.96f,  0.1f,// 24
		-0.18f, -0.5f, 0.1f,	0.95f,  0.1f,// 25
		-0.2f, -0.5f, 0.1f,		0.9f,  0.27f,// 26
		-0.2f, -0.4f, 0.1f,		0.8f,  0.27f,// 27
		0.1f , -0.55f , 0.1f,	1.0f,0.4f,  //28
		-0.1f,-0.55f,0.1f,		1.0f,0.4f,  //29

		-0.02f,-0.4f,-0.1f,    0.03f,1.0f,   //30
		-0.2f,-0.1f,-0.1f,    0.71f,0.5f,   //31
		-0.2f,0.0f,-0.1f,    0.7f,0.5f,   //32
		0.2f,0.0f,-0.1f,    0.7f,0.55f,   //33
		0.2f,-0.1f,-0.1f,    0.71f,0.55f,   //34
		0.02f,-0.4f,-0.1f,    0.03f,1.0f,   //35

		-0.02f,-0.4f,0.1f,    0.8f,0.4f,   //36
		-0.2f,-0.1f,0.1f,    0.55f,0.35f,   //37
		-0.2f,0.0f,0.1f,    0.65f,0.5f,   //38
		0.2f,0.0f,0.1f,    0.65f,0.55f,   //39
		0.2f,-0.1f,0.1f,    0.55f,0.7f,   //40
		0.02f,-0.4f,0.1f,    0.8f,0.6f,   //41

		-0.18f, -0.4f, -0.1f,	0.002f,  0.0f,// 42
		-0.18f, -0.4f, 0.1f,	0.002f,  0.1f,// 43
		0.18f, -0.4f, -0.1f,	0.01f,  0.0f,// 44
		0.18f, -0.4f, 0.1f,		0.01f,  0.1f,// 45
	};
	std::vector<GLuint> indices = {
		12,13,11,
		13,10,11,
		9,7,8,
		9,6,7,
		0,6,13,
		0,5,6,
		0,4,5,
		0,1,4,
		1,2,4,
		2,3,4,

		6,7,21,
		6,21,20,
		8,7,21,
		8,21,22,
		9,8,22,
		9,22,23,
		//10,9,23,
		//10,23,24,
		11,10,24,
		11,24,25,
		12,11,25,
		12,25,26,
		12,26,13,
		26,27,13,
		13,14,0,
		13,27,14,
		0,14,15,
		0,15,1,
		1,15,16,
		1,16,2,
		2,16,17,
		2,17,3,
		3,17,18,
		3,18,4,
		4,18,19,
		4,19,5,
		5,19,20,
		5,20,6,

		30,36,31,
		36,37,31,
		31,37,32,
		37,38,32,
		32,38,33,
		38,39,33,
		33,39,34,
		39,40,34,
		34,40,35,
		40,41,35,

		36,27,26,
		36,26,29,
		41,36,29,
		41,29,28,
		41,28,21,
		41,21,20,
		20,40,41,
		27,37,36,
		20,19,39,
		38,14,27,
		38,15,14,
		16,15,38,
		18,39,19,
		17,39,18,
		16,38,17,
		17,38,39,

		42,44,45,
		42,45,43,
	};
	std::vector<GLfloat> vertices1 = {
		-0.02f,-0.399f,-0.099f,		0.5f,0.1f,   //0
		0.02f,-0.399f,-0.099f,		0.51f,0.1f,   //5
		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4

		-0.02f,-0.399f,-0.099f,		0.5f,0.1f,   //0
		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4
		-0.199f,-0.1f,-0.099f,		0.38f,0.6f,   //1

		-0.199f,-0.1f,-0.099f,		0.38f,0.6f,   //1
		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4
		-0.199f,-0.001f,-0.099f,	0.38f,0.8f,   //2

		-0.199f,-0.001f,-0.099f,	0.38f,0.8f,   //2
		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4
		0.199f,-0.001f,-0.099f,		0.56f,0.8f,   //3

		-0.02f,-0.399f,-0.099f,		0.5f,0.1f,   //0
		0.02f,-0.399f,-0.099f,		0.51f,0.1f,   //5
		0.02f,-0.399f,0.1f,			0.51f,0.0f,   //11

		-0.02f,-0.399f,-0.099f,		0.5f,0.1f,   //0
		0.02f,-0.399f,0.1f,			0.51f,0.0f,   //11
		-0.02f,-0.399f,0.1f,		0.5f,0.0f,   //6

		0.02f,-0.399f,-0.099f,		0.51f,0.1f,   //5
		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4
		0.199f,-0.1f,0.1f,			0.56f,0.99f,   //10

		0.02f,-0.399f,-0.099f,		0.51f,0.1f,   //5
		0.199f,-0.1f,0.1f,			0.56f,0.99f,   //10
		0.02f,-0.399f,0.1f,			0.51f,0.0f,   //11

		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4
		0.199f,-0.001f,-0.099f,		0.56f,0.8f,   //3
		0.199f,-0.001f,0.1f,		0.5f,0.99f,   //9

		0.199f,-0.1f,-0.099f,		0.56f,0.6f,   //4
		0.199f,-0.001f,0.1f,		0.5f,0.99f,   //9
		0.199f,-0.1f,0.1f,			0.56f,0.99f,   //10

		0.199f,-0.001f,-0.099f,		0.56f,0.8f,   //3
		-0.199f,-0.001f,-0.099f,	0.38f,0.8f,   //2
		0.199f,-0.001f,0.1f,		0.5f,0.99f,   //9

		-0.199f,-0.001f,-0.099f,	0.38f,0.8f,   //2
		-0.199f,-0.001f,0.1f,		0.4f,0.99f,   //8
		0.199f,-0.001f,0.1f,		0.5f,0.99f,   //9

		-0.199f,-0.001f,-0.099f,	0.38f,0.8f,   //2
		-0.199f,-0.1f,-0.099f,		0.38f,0.6f,   //1
		-0.199f,-0.001f,0.1f,		0.4f,0.99f,   //8

		-0.199f,-0.1f,-0.099f,		0.38f,0.6f,   //1
		-0.199f,-0.1f,0.1f,			0.55f,0.3f,   //7
		-0.199f,-0.001f,0.1f,		0.4f,0.99f,   //8
		
		-0.199f,-0.1f,-0.099f,		0.38f,0.6f,   //1
		-0.02f,-0.399f,-0.099f,		0.5f,0.1f,   //0
		-0.02f,-0.399f,0.1f,		0.5f,0.0f,   //6

		-0.199f,-0.1f,-0.099f,		0.38f,0.6f,   //1
		-0.02f,-0.399f,0.1f,		0.5f,0.0f,   //6
		-0.199f,-0.1f,0.1f,			0.55f,0.3f,   //7
	};
	std::vector<GLuint> indices1 = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
		36,37,38,39,40,41,42,43,44,45,46,47,
	};
	std::vector<GLfloat> vertices2 = {
		-0.07f, -0.5f, -0.1f,	0.3f,0.0f,	//0
		-0.07f, 0.3f , -0.1f,	0.0f,1.0f,	//1
		0.07f,0.3f, -0.1f,		1.0f, 1.0f, //2

		-0.07f, -0.5f, -0.1f,	0.3f,0.0f,	//0
		0.07f,0.3f, -0.1f,		1.0f, 1.0f, //2
		0.07f,-0.5f, -0.1f,		0.7f,0.0f,	//3

		-0.07f, -0.5f, -0.1f,	0.3f,0.0f,	//0
		0.07f,-0.5f, -0.1f,		0.7f,0.0f,	//3
		0.07f,-0.5f, -0.05f,	0.7f,0.05f,	//9

		-0.07f, -0.5f, -0.1f,	0.3f,0.0f,	//0
		0.07f,-0.5f, -0.05f,	0.7f,0.05f,	//9
		-0.07f, -0.5f, -0.05f,	0.3f,0.05f,	//4

		-0.07f, -0.5f, -0.1f,	0.3f,0.0f,	//0
		-0.07f, -0.5f, -0.05f,	0.3f,0.05f,	//4
		-0.07f, 0.3f , -0.1f,	0.0f,1.0f,	//1

		-0.07f, 0.3f , -0.1f,	0.0f,1.0f,	//1
		-0.07f, -0.5f, -0.05f,	0.3f,0.05f,	//4
		-0.07f, 0.15f , 0.11f,	0.3f,0.9f,	//5

		-0.07f, 0.3f , -0.1f,	0.0f,1.0f,	//1
		-0.07f, 0.15f , 0.11f,	0.3f,0.9f,	//5
		-0.07f,0.3f, 0.11f,		0.3f, 1.0f, //6

		-0.07f, 0.3f , -0.1f,	0.0f,1.0f,	//1
		-0.07f,0.3f, 0.11f,		0.3f, 1.0f, //6
		0.07f,0.3f, -0.1f,		1.0f, 1.0f, //2

		-0.07f,0.3f, 0.11f,		0.3f, 1.0f, //6
		0.07f,0.3f, 0.11f,		0.7f,1.0f,	//7
		0.07f,0.3f, -0.1f,		1.0f, 1.0f, //2

		0.07f,0.3f, 0.11f,		0.7f,1.0f,	//7
		0.07f,0.15f, 0.11f,		0.7f, 0.9f, //8
		0.07f,0.3f, -0.1f,		1.0f, 1.0f, //2

		0.07f,0.15f, 0.11f,		0.7f, 0.9f, //8
		0.07f,-0.5f, -0.1f,		0.7f,0.0f,	//3
		0.07f,0.3f, -0.1f,		1.0f, 1.0f, //2

		0.07f,-0.5f, -0.05f,	0.7f,0.05f,	//9
		0.07f,-0.5f, -0.1f,		0.7f,0.0f,	//3
		0.07f,0.15f, 0.11f,		0.7f, 0.9f, //8

		-0.07f, 0.15f , 0.11f,	0.3f,0.9f,	//5
		-0.07f, -0.5f, -0.05f,	0.3f,0.05f,	//4
		0.07f,-0.5f, -0.05f,	0.7f,0.05f,	//9

		-0.07f, 0.15f , 0.11f,	0.3f,0.9f,	//5
		0.07f,-0.5f, -0.05f,	0.7f,0.05f,	//9
		0.07f,0.15f, 0.11f,		0.7f, 0.9f, //8

		-0.07f,0.3f, 0.11f,		0.3f, 1.0f, //6
		-0.07f, 0.15f , 0.11f,	0.3f,0.9f,	//5
		0.07f,0.15f, 0.11f,		0.7f, 0.9f, //8

		-0.07f,0.3f, 0.11f,		0.3f, 1.0f, //6
		0.07f,0.15f, 0.11f,		0.7f, 0.9f, //8
		0.07f,0.3f, 0.11f,		0.7f,1.0f,	//7
	};
	std::vector<GLuint> indices2 = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
		36,37,38,39,40,41,42,43,44,45,46,47,

	};
	std::vector<GLfloat> vertices3 = {
		-0.2f, -0.2f, 0.1f,		0.0f,0.0f,	//0
		-0.2f, 0.1f , 0.1f,	0.0f, 1.0f, //1
		-0.2f, 0.2f , 0.1f,  1.0f, 1.0f, //2
		-0.1f, 0.2f, 0.1f,	1.0f, 0.0f, //3
		-0.1f,0.1f, 0.1f,		1.0f, 0.0f,	//4
		0.1f,0.1f, 0.1f,		0.0f, 0.0f, //5
		0.1f, 0.2f, 0.1f,	0.0f,1.0f,	//6
		0.2f, 0.2f, 0.1f,		1.0f, 1.0f,	//7
		0.2f, 0.1f, 0.1f,		1.0f, 1.0f,	//8
		0.2f, -0.2f, 0.1f,		1.0f, 1.0f,	//9

		-0.2f, -0.2f, -0.1f,		1.0f, 1.0f,	//10
		-0.2f, 0.1f , -0.1f,			0.0f, 1.0f, //11
		-0.2f, 0.1f , 0.0f,			0.0f, 1.0f, //12
		-0.2f, 0.2f , 0.0f,  1.0f, 1.0f, //13

		0.2f, 0.2f, 0.0f,		1.0f, 1.0f,	//14
		0.2f, 0.1f, 0.0f,		1.0f, 1.0f,	//15
		0.2f, 0.1f, -0.1f,		1.0f, 1.0f,	//16
		0.2f, -0.2f, -0.1f,		1.0f, 1.0f,	//17

		-0.18f, 0.2f , 0.0f,			0.0f, 1.0f, //18
		-0.18f, 0.2f , 0.1f,			0.0f, 1.0f, //19
		-0.1f, 0.2f, -0.1f,				1.0f, 0.0f, //20

	};
	std::vector<GLuint> indices3 = {
		//top
		0,9,8,
		0,8,1,
		//side 1
		11,10,0,
		11,0,1,
		//side 2
		17,16,8,
		17,8,9,
		//bottom
		10,17,11,
		11,17,16,
		//front
		11,16,8,
		11,8,1,

	};
	std::vector<GLfloat> vertices4 = {
		-0.2f, -0.2f, 0.0f,		0.0f,0.0f,	//0
		-0.2f, -0.1f , 0.0f,	0.0f, 1.0f, //1
		-0.1f, 0.0f , 0.0f,		1.0f, 1.0f, //2
		-0.05f, 0.1f, 0.0f,		1.0f, 0.0f, //3
		0.05f,  0.1f, 0.0f,		1.0f, 0.0f,	//4
		0.1f, 0.0f , 0.0f,		1.0f, 1.0f, //5
		0.2f, -0.1f, 0.0f,		1.0f, 0.0f, //6
		0.2f,-0.2f, 0.0f,		1.0f, 0.0f,	//7

		-0.2f, -0.2f, -0.1f,		0.0f,0.0f,	//8
		-0.2f, -0.1f , -0.1f,	0.0f, 1.0f, //9
		-0.1f, 0.0f , -0.1f,		1.0f, 1.0f, //10
		-0.05f, 0.1f, -0.1f,		1.0f, 0.0f, //11
		0.05f,  0.1f, -0.1f,		1.0f, 0.0f,	//12
		0.1f, 0.0f , -0.1f,		1.0f, 1.0f, //13
		0.2f, -0.1f,-0.1f,		1.0f, 0.0f, //14
		0.2f,-0.2f, -0.1f,		1.0f, 0.0f,	//15

		-0.04f, -0.2f, -0.8f,		0.0f,0.0f,	//16
		-0.04f, -0.14f , -0.8f,	0.0f, 1.0f, //17
		-0.02f, -0.13f , -0.8f,		1.0f, 1.0f, //18
		-0.01f, -0.11f, -0.8f,		1.0f, 0.0f, //19
		0.01f,  -0.11f, -0.8f,		1.0f, 0.0f,	//20
		0.02f, -0.13f , -0.8f,		1.0f, 1.0f, //21
		0.04f, -0.14f,-0.8f,		1.0f, 0.0f, //22
		0.04f,-0.2f, -0.8f,		1.0f, 0.0f,	//23
	};
	std::vector<GLuint> indices4 = {
		//front
		0,7,6,
		0,6,1,
		1,6,5,
		1,5,2,
		5,4,3,
		2,5,3,
		// front 2
		8,15,14,
		8,14,9,
		9,14,13,
		9,13,10,
		13,12,11,
		10,13,11,
		//side 1
		0,1,8,
		1,9,8,
		//side 2
		1,2,10,
		1,10,9,
		//side 3
		2,3,11,
		2,11,10,
		//side 4
		3,4,12,
		3,12,11,
		//side 5
		4,5,13,
		4,13,12,
		//side 6
		5,6,14,
		5,14,13,
		//side 7
		6,7,15,
		6,15,14,
		//front 3
		16,23,22,
		16,22,17,
		17,22,21,
		17,21,18,
		21,20,19,
		18,21,19,
		//side 8
		8,9,16,
		9,17,16,
		//side 9
		17,18,10,
		17,10,9,
		//side 10
		18,19,11,
		18,11,10,
		//side 11
		19,20,12,
		19,12,11,
		//side 12
		20,21,13,
		20,13,12,
		//side 13
		21,22,14,
		21,14,13,
		//side 14
		22,23,15,
		22,15,14,

	};
	ShaderProgram *basicShader;
	Object3D *part1;
	Object3D *part2;
	Object3D *part3;
	Object3D *part4;
	Object3D *part5;
public:
	Kadlub(const glm::vec3& centerPoint, const glm::vec3& scaleVector,ShaderProgram *basicShader);
};

