#include "Kadlub.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Kadlub::Kadlub() :
	basicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag"),
	spoilerModel(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)) {
	part1 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part2 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part3 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part4 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));

	part1->set_geometry(this->vertices, this->indices);
	part2->set_geometry(this->vertices1, this->indices1);
	part3->set_geometry(this->vertices2, this->indices2);
	part4->set_geometry(this->vertices3, this->indices3);

	part1->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	part2->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	part3->translate(glm::vec3(0.0f, -1.4f, 0.001f));
	part4->translate(glm::vec3(0.0f, 1.6f, 0.0f));

	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/chassis1.png"));
	part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/red.png"));
	part3->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/chassis2.png"));
	part4->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/orange.png"));

	spoilerModel.add(part1);
	spoilerModel.add(part2);
	spoilerModel.add(part3);
	spoilerModel.add(part4);
	spoilerModel.bind_buffers();


}

Kadlub::~Kadlub() {
	spoilerModel.free_buffers();
}
void Kadlub::draw(glm::mat4& m) {
	spoilerModel.draw(m);
}
void Kadlub::translate(const glm::vec3& translateVector) {
	this->spoilerModel.translate(translateVector);
}
void Kadlub::rotate(float angle, const glm::vec3& rotationAxis) {
	spoilerModel.rotate(angle, rotationAxis);
}
void Kadlub::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	spoilerModel.rotate(angle, rotationAxis, fixedPoint);
}
void Kadlub::scale(const glm::vec3& scaleVector) {
	spoilerModel.scale(scaleVector);
}
void Kadlub::setProjectionView(glm::mat4 p, glm::mat4 v) {
	GLint projLoc = glGetUniformLocation(basicShader.get_programID(), "projection");
	// setup view matrix - get it from camera object
	GLint viewLoc = glGetUniformLocation(basicShader.get_programID(), "view");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(box1.model_));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(p));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(v));
}
void Kadlub::shaderUse() {
	basicShader.Use();
}