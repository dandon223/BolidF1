/**
* Author: Konrad Bratosiewicz 
* Lamp post implementation
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

#include "utils.h"
#include "shprogram.h"
#include "Model.h"
#include "Light.h"
#include "Cube.h"

class LampPost: public Model {
	LightSource* light_;
public:
	LampPost(const ShaderProgram *, const ShaderProgram *, std::vector<LightSource *>&);
	virtual void translate(const glm::vec3&);
	virtual void rotate(float, const glm::vec3&);
};