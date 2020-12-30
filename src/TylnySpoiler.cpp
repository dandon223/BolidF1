#include "include/TylnySpoiler.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TylnySpoiler::TylnySpoiler(const glm::vec3& centerPoint, const glm::vec3& scaleVector,ShaderProgram *sp) :  Model(centerPoint, scaleVector) {
	this->basicShader = sp;
	part1 = new Object3D(glm::vec3(-0.82, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part12 = new Object3D(glm::vec3(-0.81, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0),(this->basicShader));
	part2 = new Object3D(glm::vec3(0.82, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part22 = new Object3D(glm::vec3(0.81, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	wing1 = new Object3D(glm::vec3(0.0, 0.3, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	wing2 = new Object3D(glm::vec3(0.0, -0.1, 0.0), glm::vec3(1.0, 1.0, 1.0),(this->basicShader));
	part3 = new Object3D(glm::vec3(0.2, -0.59, 0.3), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part4 = new Object3D(glm::vec3(-0.2, -0.59, 0.3), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));

	part1->set_geometry(this->vertices, this->indices);
	part12->set_geometry(vertices1, indices1);
	part2->set_geometry(vertices, indices);
	part22->set_geometry(vertices1, indices1);
	wing1->set_geometry(vertices2, indices2);
	wing2->set_geometry(vertices2, indices2);
	part3->set_geometry(vertices3, indices3);
	part4->set_geometry(vertices3, indices3);

	part1->translate(glm::vec3(0.0, -0.2, -0.15));
	part12->translate( glm::vec3(0.0, -0.2, -0.15));
	part2->translate( glm::vec3(0.0, -0.2, -0.15));
	part22->translate( glm::vec3(0.0, -0.2, -0.15));
	wing1->translate( glm::vec3(0.0, -0.2, -0.15));
	wing2->translate(glm::vec3(0.0, -0.2, -0.15));
	part3->translate(glm::vec3(0.0, -0.0, -0.3));
	part4->translate(glm::vec3(0.0, -0.0, -0.3));

	part1->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part12->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part2->rotate(270, glm::vec3(0.0, 1.0, 0.0));
	part22->rotate(270, glm::vec3(0.0, 1.0, 0.0));
	part3->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part4->rotate(90, glm::vec3(0.0, 1.0, 0.0));

	part1->scale(glm::vec3(-0.4f,-0.4f,-0.0f));
	part12->scale(glm::vec3(-0.4f, -0.4f, -0.0f));
	part2->scale(glm::vec3(-0.4f, -0.4f, -0.0f));
	part22->scale(glm::vec3(-0.4f, -0.4f, -0.0f));

	wing1->scale(glm::vec3(-0.0f, -0.0f, -0.6f));
	wing2->scale(glm::vec3(-0.0f, -0.0f, -0.6f));

	part3->scale(glm::vec3(-0.0f, -0.4f, -0.0f));
	part4->scale(glm::vec3(-0.0f, -0.4f, -0.0f));


	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
	part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
	part12->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part22->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	wing1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	wing2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part3->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part4->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));


	this->add(part1);
	this->add(part12);
	this->add(part2);
	this->add(part22);

	this->add(wing1);
	this->add(wing2);

	this->add(part3);
	this->add(part4);

	//this->bind_buffers();


}

