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

class Bolid {
private:
	PrzedniSpoiler przedniSpoiler;
	TylnySpoiler tylnySpoiler;
	Kadlub kadlub;
	ShaderProgram basicShader;
public:
	Bolid();
	virtual void draw(glm::mat4& = glm::mat4());

	void translate(const glm::vec3&);
	void rotate(float, const glm::vec3&);
	void rotate(float, const glm::vec3&, const glm::vec3&);
	void scale(const glm::vec3&);
	void setProjectionView(glm::mat4 p, glm::mat4 w);
	void shaderUse();
};
