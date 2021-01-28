/**
 * Author: Konrad Bratosiewicz
 * Street lights implementation
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
#include "LampPost.h"

class StreetLamps : public Model {

public:
	StreetLamps(const glm::vec3&, const glm::vec3&, const ShaderProgram*, const ShaderProgram*, std::vector<LightSource*>&);
	void draw(float bolid_center_z, glm::mat4 & = glm::mat4());
};
