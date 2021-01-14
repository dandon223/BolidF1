#include "include/Kolo.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Kola::Kola(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram *sp, GLfloat radius = 5, GLint numOfSides = 10, GLfloat width = 5) : Model(centerPoint, scaleVector) {
	this->basicShader = sp;
	_radius = radius;
	_numOfSides = numOfSides;
	_width = width;
	createCircle();
	makeTire();
	makeBeam();

	for (int i = 0; i < 6; ++i) {
		
		tylnaOs[i] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
		tylnaBelkaStabilizatora[i] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));

		przedniaOs[i] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
		przedniaBelkaStabilizatora[i] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));
		przedniaBelkaStabilizatora[i+6] = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), (this->basicShader));

	}

	for (int i = 0; i < 2; ++i) {

		tylnaOs[3*i]->set_geometry(this->vertices, this->indicesCir);
		tylnaOs[3*i + 1]->set_geometry(this->vertices2, this->indicesCir);
		tylnaOs[3*i + 2]->set_geometry(this->verticesTire, this->indicesTire);

		przedniaOs[3*i]->set_geometry(this->vertices, this->indicesCir);
		przedniaOs[3*i + 1]->set_geometry(this->vertices2, this->indicesCir);
		przedniaOs[3*i + 2]->set_geometry(this->verticesTire, this->indicesTire);

		tylnaBelkaStabilizatora[3 * i]->set_geometry(this->verticesBeam, this->indicesSquare);
		tylnaBelkaStabilizatora[3 * i + 1]->set_geometry(this->verticesBeam2, this->indicesSquare);
		tylnaBelkaStabilizatora[3 * i + 2]->set_geometry(this->verticesBeamCon, this->indicesBeam);
	}

	for (int i = 0; i < 4; ++i)
	{
		przedniaBelkaStabilizatora[3*i]->set_geometry(this->verticesBeam, this->indicesSquare);
		przedniaBelkaStabilizatora[3*i + 1]->set_geometry(this->verticesBeam2, this->indicesSquare);
		przedniaBelkaStabilizatora[3*i + 2]->set_geometry(this->verticesBeamCon, this->indicesBeam);
	}

	for (int i = 0; i < 6; ++i) {
		//LEWA STRONA
		if (i / 3 < 1) {
			tylnaOs[i]->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
			tylnaOs[i]->translate(glm::vec3(0.85f, 1.5f, -1.7f));

			przedniaOs[i]->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
			przedniaOs[i]->translate(glm::vec3(0.85f, 1.35f, 1.3f));
			przedniaOs[i]->scale(glm::vec3(-0.375f, -0.375f, -0.375f));

			tylnaBelkaStabilizatora[i]->translate(glm::vec3(0.f, 1.4f, -1.7));
			tylnaBelkaStabilizatora[i]->rotate(90, glm::vec3(0.0f, 1.0f, 0.0f));

			przedniaBelkaStabilizatora[i]->translate(glm::vec3(0.f, 1.34f, 1.18f));
			przedniaBelkaStabilizatora[i]->rotate(80, glm::vec3(0.0f, 1.0f, 0.0f));
			przedniaBelkaStabilizatora[i + 6]->translate(glm::vec3(0.f, 1.34f, 1.45f));
			przedniaBelkaStabilizatora[i + 6]->rotate(100, glm::vec3(0.0f, 1.0f, 0.0f));
		
		}
		else {
			//PRAWA STRONA
			tylnaOs[i]->rotate(-270, glm::vec3(0.0f, 1.0f, 0.0f));
			tylnaOs[i]->translate(glm::vec3(-0.85f, 1.5f, -1.7f));

			przedniaOs[i]->rotate(-270, glm::vec3(0.0f, 1.0f, 0.0f));
			przedniaOs[i]->translate(glm::vec3(-0.85f, 1.35f, 1.3f));
			przedniaOs[i]->scale(glm::vec3(-0.375f, -0.375f, -0.375f));

			tylnaBelkaStabilizatora[i]->translate(glm::vec3(0.f, 1.4f, -1.7));
			tylnaBelkaStabilizatora[i]->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));

			przedniaBelkaStabilizatora[i]->translate(glm::vec3(0.f, 1.34f, 1.16f));
			przedniaBelkaStabilizatora[i]->rotate(-80, glm::vec3(0.0f, 1.0f, 0.0f));
			przedniaBelkaStabilizatora[i + 6]->translate(glm::vec3(0.f, 1.34f, 1.43f));
			przedniaBelkaStabilizatora[i + 6]->rotate(-100, glm::vec3(0.0f, 1.0f, 0.0f));

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
	
	przedniaBelkaStabilizatora[0]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));
	przedniaBelkaStabilizatora[1]->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/opona.png"));


	for (int i = 0; i < 6; ++i) {
		this->add(tylnaOs[i]);
		this->add(przedniaOs[i]);
		this->add(tylnaBelkaStabilizatora[i]);
		this->add(przedniaBelkaStabilizatora[i]);
		this->add(przedniaBelkaStabilizatora[i+6]);
	}
	//this->bind_buffers();

}



void Kola::createCircle()
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

void Kola::makeTire()
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

void Kola::makeBeam() {
	verticesBeam2 = verticesBeam;
	for (GLuint i = 0; i < verticesBeam.size() / 5; ++i) {
		verticesBeam2[5 * i + 2] += 0.7f;
	}

	GLint verticesSize = verticesBeam.size() / 5;

	for (int i = 0; i < verticesSize; ++i) {
		indicesBeam.push_back(i);
		indicesBeam.push_back(((i + 1) % verticesSize) + verticesSize);
		indicesBeam.push_back(i + verticesSize);

		indicesBeam.push_back((i + 1) % verticesSize);
		indicesBeam.push_back(((i + 1) % verticesSize) + verticesSize);
		indicesBeam.push_back(i);
	}

	verticesBeamCon.insert(verticesBeamCon.end(), verticesBeam.begin(), verticesBeam.end());
	verticesBeamCon.insert(verticesBeamCon.end(), verticesBeam2.begin(), verticesBeam2.end());

}



