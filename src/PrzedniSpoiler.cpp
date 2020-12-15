#include "PrzedniSpoiler.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PrzedniSpoiler::PrzedniSpoiler() :
	basicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag"),
	spoilerModel(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)) {
	part1 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part2 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));

	part1->set_geometry(this->vertices, this->indices);
	part2->set_geometry(this->vertices1, this->indices1);

	part2->rotate(90, glm::vec3(1.0, 0.0, 0.0));
	part2->rotate(180, glm::vec3(0.0, 0.0, 1.0));
	part2->translate(glm::vec3(0.0f,0.4f,0.0f));

	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "przedniSpoiler1.png"));
	part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/przedniSpoiler2.png"));

	spoilerModel.add(part1);
	spoilerModel.add(part2);
	spoilerModel.bind_buffers();


}

PrzedniSpoiler::~PrzedniSpoiler() {
	spoilerModel.free_buffers();
}
void PrzedniSpoiler::draw(glm::mat4& m) {
	spoilerModel.draw(m);
}
void PrzedniSpoiler::translate(const glm::vec3& translateVector) {
	this->spoilerModel.translate(translateVector);
}
void PrzedniSpoiler::rotate(float angle, const glm::vec3& rotationAxis) {
	spoilerModel.rotate(angle, rotationAxis);
}
void PrzedniSpoiler::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	spoilerModel.rotate(angle, rotationAxis, fixedPoint);
}
void PrzedniSpoiler::scale(const glm::vec3& scaleVector) {
	spoilerModel.scale(scaleVector);
}
void PrzedniSpoiler::setProjectionView(glm::mat4 p, glm::mat4 v) {
	GLint projLoc = glGetUniformLocation(basicShader.get_programID(), "projection");
	// setup view matrix - get it from camera object
	GLint viewLoc = glGetUniformLocation(basicShader.get_programID(), "view");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(box1.model_));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(p));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(v));
}
void PrzedniSpoiler::shaderUse() {
	basicShader.Use();
}