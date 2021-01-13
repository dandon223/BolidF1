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
#include "PrzedniSpoiler.h"
#include "TylnySpoiler.h"
#include "Kadlub.h"
#include "Light.h"

class Bolid : public Model {
private:
	PrzedniSpoiler *przedniSpoiler;
	TylnySpoiler *tylnySpoiler;
	Kadlub *kadlub;
public:
	Bolid(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram*);
	void setProjectionView(glm::mat4 p, glm::mat4 w);
	void shaderUse();
};
