#include "TylnySpoiler.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TylnySpoiler::TylnySpoiler() : 
basicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag"),
spoilerModel(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)) {
	part1 = new Object3D(glm::vec3(-0.82, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part12 = new Object3D(glm::vec3(-0.81, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part2 = new Object3D(glm::vec3(0.82, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part22 = new Object3D(glm::vec3(0.81, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	wing1 = new Object3D(glm::vec3(0.0, 0.3, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	wing2 = new Object3D(glm::vec3(0.0, -0.1, 0.0), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part3 = new Object3D(glm::vec3(0.2, -0.59, 0.3), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));
	part4 = new Object3D(glm::vec3(-0.2, -0.59, 0.3), glm::vec3(1.0, 1.0, 1.0), &(this->basicShader));

	part1->set_geometry(this->vertices, this->indices);
	part12->set_geometry(vertices1, indices1);
	part2->set_geometry(vertices, indices);
	part22->set_geometry(vertices1, indices1);
	wing1->set_geometry(vertices2, indices2);
	wing2->set_geometry(vertices2, indices2);
	part3->set_geometry(vertices3, indices3);
	part4->set_geometry(vertices3, indices3);

	part1->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part12->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part2->rotate(270, glm::vec3(0.0, 1.0, 0.0));
	part22->rotate(270, glm::vec3(0.0, 1.0, 0.0));
	part3->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part4->rotate(90, glm::vec3(0.0, 1.0, 0.0));


	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
	part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
	part12->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part22->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	wing1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	wing2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part3->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part4->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));


	spoilerModel.add(part1);
	spoilerModel.add(part12);
	spoilerModel.add(part2);
	spoilerModel.add(part22);
	spoilerModel.add(wing1);
	spoilerModel.add(wing2);
	spoilerModel.add(part3);
	spoilerModel.add(part4);
	spoilerModel.bind_buffers();

}
TylnySpoiler::~TylnySpoiler() {
	spoilerModel.free_buffers();
}
void TylnySpoiler::draw(glm::mat4& m) {
	basicShader.Use();
	spoilerModel.draw(m);
}
void TylnySpoiler::translate(const glm::vec3& translateVector) {
	this->spoilerModel.translate( translateVector);
}
void TylnySpoiler::rotate(float angle, const glm::vec3& rotationAxis) {
	spoilerModel.rotate(angle, rotationAxis);
}
void TylnySpoiler::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	spoilerModel.rotate(angle,  rotationAxis,  fixedPoint);
}
void TylnySpoiler::scale(const glm::vec3& scaleVector) {
	spoilerModel.scale(scaleVector);
}