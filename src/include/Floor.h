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

class Floor {
private:
	std::vector<GLfloat> vertices = {
		-1.0f, -1.0f, 0.0f,		0.0f,  0.0f,// 0
		-1.0f, 1.0f, 0.0f,		0.0f,  10000.0f,// 1
		1.0f, 1.0f, 0.0f,		10000.0f,  10000.0f,// 2
		1.0f, -1.0f, 0.0f,		10000.0f,  0.0f,// 3
	};
	std::vector<GLuint> indices = {
		0, 1, 2,
		2, 3, 0,
	};

	ShaderProgram *basicShader;
	Model model;
	Object3D *part1;

public:
	Floor(ShaderProgram *sp);
	virtual void draw(glm::mat4& = glm::mat4());
};