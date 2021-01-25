/**
 * Author: Konrad Bratosiewicz
 * Road implementation
 **/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include "include/utils.h"
#include "include/shprogram.h"
#include "Object3D.h"

class Road : public Object3D {
	const std::vector<GLfloat> VERTICES = {
		-6.0f, -6.0f, 0.0f,		0.0f,  0.0f, // 0
		-6.0f,  6.0f, 0.0f,		0.0f,  1.0f, // 1
		 6.0f,  6.0f, 0.0f,		1.0f,  1.0f, // 2
		 		
		-6.0f, -6.0f, 0.0f,		0.0f,  0.0f, // 0
		 6.0f,  6.0f, 0.0f,		1.0f,  1.0f, // 2
		 6.0f, -6.0f, 0.0f,		1.0f,  0.0f, // 3
	};

	const std::vector<GLuint> INDICES = {
		0, 1, 2,
		3, 4, 5
	};

public:
	Road(ShaderProgram*);
};