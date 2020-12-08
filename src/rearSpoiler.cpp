#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rearSpoiler.h"

RearSpoiler::RearSpoiler(const GLchar* image1Path, const GLchar* image2Path, ShaderProgram & shaderProgram , Camera &c) : camera(c),Program(shaderProgram) {
	this->translateVector = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotationPoint = glm::vec3(0.0f, 0.0f, 0.0f); //-0.1f, -0.55f, 0.0f
	this->rotAngleX = 0.0f;
	this->rotAngleY = 0.0f;
	this->rotAngleZ = 0.0f;
	int width, height;
	unsigned char* image = SOIL_load_image("spoiler.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture0;
	glGenTextures(1, &texture0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// freeing unnecessary texture stuff
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->Texture1_id = texture0;

	int width1, height1;
	unsigned char* image1 = SOIL_load_image("carbon.png", &width1, &height1, 0, SOIL_LOAD_RGB);
	if (image1 == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture1;
	glGenTextures(1, &texture1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	// freeing unnecessary texture stuff
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->Texture2_id = texture1;

	glGenVertexArrays(4, this->VAO);
	glGenBuffers(4, this->VBO);
	glGenBuffers(4, this->EBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindVertexArray(VAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
void RearSpoiler::Draw() {
	Program.Use();

	glm::mat4 trans;

	trans = glm::translate(trans, this->rotationPoint);
	trans = glm::rotate(trans, glm::radians(this->rotAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(this->rotAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::rotate(trans, -glm::radians(this->rotAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::translate(trans, -this->rotationPoint);


	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -0.75f) + this->translateVector);


	int transID = glGetUniformLocation(Program.get_programID(), "transform");
	glUniformMatrix4fv(transID, 1, GL_FALSE, glm::value_ptr(trans));

	// setup projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera.fov_), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(Program.get_programID(), "projection");

	// setup view matrix - get it from camera object
	glm::mat4 view = camera.getViewMatrix();
	GLint viewLoc = glGetUniformLocation(Program.get_programID(), "view");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture1_id);
	glUniform1i(glGetUniformLocation(Program.get_programID(), "Texture"), 0);

	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);


	glBindTexture(GL_TEXTURE_2D, Texture2_id);

	glBindVertexArray(VAO[1]);
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(Program.get_programID(), "Texture"), 0);

	glDrawElements(GL_TRIANGLES, _countof(indices1), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 1.5f));
	trans = glm::rotate(trans, -glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(transID, 1, GL_FALSE, glm::value_ptr(trans));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture1_id);
	glUniform1i(glGetUniformLocation(Program.get_programID(), "Texture"), 0);

	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, Texture2_id);

	glBindVertexArray(VAO[1]);
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(Program.get_programID(), "Texture"), 0);

	glDrawElements(GL_TRIANGLES, _countof(indices1), GL_UNSIGNED_INT, 0);

	trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));

	trans = glm::translate(trans, glm::vec3(-0.2f, 0.1f, -0.51f));
	trans = glm::rotate(trans, -glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));

	glUniformMatrix4fv(transID, 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(VAO[2]);
	glDrawElements(GL_TRIANGLES, _countof(indices2), GL_UNSIGNED_INT, 0);

	trans = glm::translate(trans, glm::vec3(0.0f, -0.3f, 0.0f));
	glUniformMatrix4fv(transID, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, _countof(indices2), GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO[3]);

	trans = glm::translate(trans, glm::vec3(0.0f, 0.3f, 0.0f));
	trans = glm::rotate(trans, -glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));


	trans = glm::translate(trans, glm::vec3(0.05f, -0.62f, -0.04f));
	glUniformMatrix4fv(transID, 1, GL_FALSE, glm::value_ptr(trans));

	glDrawElements(GL_TRIANGLES, _countof(indices3), GL_UNSIGNED_INT, 0);

	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -0.4f));
	glUniformMatrix4fv(transID, 1, GL_FALSE, glm::value_ptr(trans));

	glDrawElements(GL_TRIANGLES, _countof(indices3), GL_UNSIGNED_INT, 0);

}
void RearSpoiler::SetProgram(ShaderProgram theProgram) {
	this->Program = theProgram;
}
glm::vec3 RearSpoiler::GetTransVector() {
	return this->translateVector;
}
void RearSpoiler::SetTransVector(glm::vec3 newTransVector) {
	this->translateVector = newTransVector;
}
void RearSpoiler::SetRotationAngleX(float newAngle) {
	this->rotAngleX = newAngle;
}
void RearSpoiler::SetRotationAngleY(float newAngle) {
	this->rotAngleY = newAngle;
}
void RearSpoiler::SetRotationAngleZ(float newAngle) {
	this->rotAngleZ = newAngle;
}

void RearSpoiler::SetRotPoint(glm::vec3 newRotPoint) {
	this->rotationPoint = newRotPoint;
}
glm::vec3 RearSpoiler::GetRotPoint() {
	return this->rotationPoint;
}