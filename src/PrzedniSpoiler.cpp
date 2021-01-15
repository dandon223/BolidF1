#include "include/PrzedniSpoiler.h"
#include "include/utils.h"


PrzedniSpoiler::PrzedniSpoiler(const glm::vec3& centerPoint, const glm::vec3& scaleVector,ShaderProgram *sp) :Model(centerPoint, scaleVector) {
	this->basicShader = sp;
	part1 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part2 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part3 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part4 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));

	part1->set_geometry(this->vertices, this->indices);
	part2->set_geometry(this->vertices1, this->indices1);
	part3->set_geometry(this->vertices2, this->indices2);
	part4->set_geometry(this->vertices2, this->indices2);

	part2->rotate(110, glm::vec3(1.0, 0.0, 0.0));
	part2->rotate(180, glm::vec3(0.0, 0.0, 1.0));
	part3->rotate(90, glm::vec3(0.0, 1.0, 0.0));
	part4->rotate(90, glm::vec3(0.0, 1.0, 0.0));

	part1->translate(glm::vec3(0.0f, 0.02f, -0.36f));
	part2->translate(glm::vec3(0.0f,0.1f,0.05f));
	part3->translate(glm::vec3(-0.5f, 0.1f, -0.1f));
	part4->translate(glm::vec3(0.5f, 0.1f, -0.1f));

	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "przedniSpoiler1.png"));
	part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/przedniSpoiler2.png"));
	part3->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
	part4->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));

	this->add(part1);
	this->add(part2);
	this->add(part3);
	this->add(part4);
}