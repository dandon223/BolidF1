#include "include/Kolo.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Kolo::Kolo(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram *sp, GLfloat radius = 5, GLint numOfSides = 10, GLfloat width = 5) : Model(centerPoint, scaleVector) {
	this->basicShader = sp;
	_radius = radius;
	_numOfSides = numOfSides;
	_width = width;
	createCircle();
	makeTire();

	for (int i = 0; i < 6; ++i) {
		tylnaOs[i] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
		przedniaOs[i] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
	}
	//Lewe ko這
	tylnaOs[0]->set_geometry(this->vertices, this->indicesCir);
	tylnaOs[1]->set_geometry(this->vertices2, this->indicesCir);
	tylnaOs[2]->set_geometry(this->verticesTire, this->indicesTire);
	//Prawe ko這
	tylnaOs[3]->set_geometry(this->vertices, this->indicesCir);
	tylnaOs[4]->set_geometry(this->vertices2, this->indicesCir);
	tylnaOs[5]->set_geometry(this->verticesTire, this->indicesTire);

	//Lewe ko這
	przedniaOs[0]->set_geometry(this->vertices, this->indicesCir);
	przedniaOs[1]->set_geometry(this->vertices2, this->indicesCir);
	przedniaOs[2]->set_geometry(this->verticesTire, this->indicesTire);
	//Prawe ko這
	przedniaOs[3]->set_geometry(this->vertices, this->indicesCir);
	przedniaOs[4]->set_geometry(this->vertices2, this->indicesCir);
	przedniaOs[5]->set_geometry(this->verticesTire, this->indicesTire);

	for (int i = 0; i < 6; ++i) {
		
		if (i / 3 < 1) {
			tylnaOs[i]->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
			tylnaOs[i]->translate(glm::vec3(0.85f, 1.5f, -1.7f));

			przedniaOs[i]->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
			przedniaOs[i]->translate(glm::vec3(0.85f, 1.5f, -1.7f));
			przedniaOs[i]->translate(glm::vec3(0.0f, -0.15f, 3.f));
			przedniaOs[i]->scale(glm::vec3(-0.375f, -0.375f, -0.375f));
		}
		else {
			tylnaOs[i]->rotate(-270, glm::vec3(0.0f, 1.0f, 0.0f));
			tylnaOs[i]->translate(glm::vec3(-0.85f, 1.5f, -1.7f));

			przedniaOs[i]->rotate(-270, glm::vec3(0.0f, 1.0f, 0.0f));
			przedniaOs[i]->translate(glm::vec3(-0.85f, 1.5f, -1.7f));
			przedniaOs[i]->translate(glm::vec3(0.0f, -0.15f, 3.f));
			przedniaOs[i]->scale(glm::vec3(-0.375f, -0.375f, -0.375f));
		}
	}

	tylnaOs[0]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	tylnaOs[1]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	tylnaOs[3]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	tylnaOs[4]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));

	przedniaOs[0]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	przedniaOs[1]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	przedniaOs[3]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	przedniaOs[4]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	
	for (int i = 0; i < 6; ++i) {
		this->add(tylnaOs[i]);
		this->add(przedniaOs[i]);
	}
	//this->bind_buffers();

}



void Kolo::createCircle()
{
	GLfloat doublePi = 2.0f * 3.14159265358979323846;

	/*std::vector<GLfloat> vertices = { _x, _y, _z, 0.01f, 0.01f };
	std::vector<GLuint> indices;*/

	for (int i = 0; i < _numOfSides; i++) {
		/*vertices.push_back(0.f + (_radius * cos(i * doublePi / _numOfSides)));
		vertices.push_back(0.f + (_radius * sin(i * doublePi / _numOfSides)));*/
		GLfloat tempX = 0.f + (_radius * cos(i * doublePi / _numOfSides));
		GLfloat tempY = 0.f + (_radius * sin(i * doublePi / _numOfSides));

		vertices.push_back(tempX);
		vertices.push_back(tempY);
		vertices.push_back(0.f);
		vertices.push_back((tempX + _radius) / (2 * _radius));
		vertices.push_back((tempY + _radius) / (2 * _radius));

		indicesCir.push_back(0);
		if (i == _numOfSides - 1) {
			indicesCir.push_back(1);
		}
		else {
			indicesCir.push_back(i + 2);
		}
		indicesCir.push_back(i + 1);
	}

}

void Kolo::makeTire()
{
	vertices2 = vertices;
	for (GLuint i = 0; i < vertices.size() / 5; ++i) {
		vertices2[5 * i + 2] += _width;
	}

	GLint verticesSize = vertices.size() / 5 - 1;

	for (int i = 0; i < verticesSize; ++i) {
		indicesTire.push_back(i);
		indicesTire.push_back(((i + 1) % verticesSize) + verticesSize);
		indicesTire.push_back(i + verticesSize);

		indicesTire.push_back((i + 1) % verticesSize);
		indicesTire.push_back(((i + 1) % verticesSize) + verticesSize);
		indicesTire.push_back(i);
	}
	verticesTire.insert(verticesTire.end(), vertices.begin() + 5, vertices.end());
	verticesTire.insert(verticesTire.end(), vertices2.begin() + 5, vertices2.end());
}

