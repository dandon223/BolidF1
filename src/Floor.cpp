#include "Floor.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Floor::Floor(ShaderProgram *sp):
	model(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)) 
{
	this->basicShader = sp;
	part1 = new Object3D(glm::vec3(-0.82, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	part1->set_geometry(this->vertices, this->indices);
	part1->translate(glm::vec3(0.0, -1.0, 0.0));
	part1->rotate(90, glm::vec3(1.0, 0.0, 0.0));
	part1->scale(glm::vec3(10000.0f, 10000.0f, 0.0f));
	part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/grass.png"));
	model.add(part1);
	model.bind_buffers();

}
void Floor::draw(glm::mat4& m) {
	model.draw(m);
}
