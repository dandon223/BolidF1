#include "include/Kadlub.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Kadlub::Kadlub(const glm::vec3& centerPoint, const glm::vec3& scaleVector,ShaderProgram *sp) :Model(centerPoint, scaleVector){
	this->basicShader = sp;
	part1 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part2 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part3 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part4 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part5 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));

	part1->set_geometry(this->vertices, this->indices);
	part2->set_geometry(this->vertices1, this->indices1);
	part3->set_geometry(this->vertices2, this->indices2);
	part4->set_geometry(this->vertices3, this->indices3);
	part5->set_geometry(this->vertices4, this->indices4);

	//part5->scale(glm::vec3(0.0f, -0.1f, 0.0f));

	part1->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	part2->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	part3->translate(glm::vec3(0.0f, -1.4f, 0.001f));
	part4->translate(glm::vec3(0.0f, 1.6f, 0.0f));
	part5->translate(glm::vec3(0.0f, 0.0f, 0.5f));

	part5->rotate(90,glm::vec3(1.0f, 0.0f, 0.0f));

	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/chassis1.png"));
	part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/red.png"));
	part3->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/chassis2.png"));
	part4->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/orange.png"));
	part5->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/orange.png"));

	this->add(part1);
	this->add(part2);
	this->add(part3);
	this->add(part4);
	this->add(part5);
	//this->bind_buffers();


}