#include "Bolid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Bolid::Bolid() :
	basicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag") ,kadlub(),przedniSpoiler(),tylnySpoiler(){
	tylnySpoiler.translate(glm::vec3(0.0f, 2.3f, -1.7f));
	kadlub.scale(glm::vec3(1.0f, 1.0f, 1.0f));
	kadlub.translate(glm::vec3(0.0f, 1.5f, 0.0f));
	kadlub.rotate(-90, glm::vec3(1.0f, 0.0f, 0.0f));
	przedniSpoiler.translate(glm::vec3(0.0, 1.3, 1.9));
	przedniSpoiler.rotate(180, glm::vec3(0.0, 1.0, 0.0));

}
void Bolid::draw(glm::mat4& m) {
	kadlub.draw(m);
	przedniSpoiler.draw(m);
	tylnySpoiler.draw(m);
}
void Bolid::setProjectionView(glm::mat4 p, glm::mat4 v) {
	GLint projLoc = glGetUniformLocation(basicShader.get_programID(), "projection");
	// setup view matrix - get it from camera object
	GLint viewLoc = glGetUniformLocation(basicShader.get_programID(), "view");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(box1.model_));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(p));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(v));
	kadlub.setProjectionView(p, v);
	przedniSpoiler.setProjectionView(p, v);
	tylnySpoiler.setProjectionView(p, v);
}
void Bolid::shaderUse() {
	basicShader.Use();
	kadlub.shaderUse();
	przedniSpoiler.shaderUse();
	tylnySpoiler.shaderUse();
}
