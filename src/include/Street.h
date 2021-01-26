/**
 * Author: Konrad Bratosiewicz
 * Street implementation
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
#include "RoadSegment.h"

class Street : public Model {

public:
	Street(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram*);
};