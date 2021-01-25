#include "include/Light.h"
#include <string>
#include <iostream>

LightSource::LightSource(
	const glm::vec3& centerPoint,
	const glm::vec3& lightColor, 
	const float ambientStrength,
	const float diffuseStrength, 
	const float specularStrength, 
	const float constant,
	const float linear,
	const float quadratic,
	const ShaderProgram* shader) : 
		Object3D(centerPoint, glm::vec3(1.0, 1.0, 1.0), shader), 
		lightColor_(lightColor),
		ambientStrength_(ambientStrength), 
		diffuseStrength_(diffuseStrength),
		specularStrength_(specularStrength),
		constant_(constant),
		linear_(linear),
		quadratic_(quadratic) {}

void LightSource::bind_buffers() {
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertices_.size(), this->vertices_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices_.size(), this->indices_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void LightSource::draw(glm::mat4& compositeModel) {
	if (shader_ == nullptr)
		return;

	glUniform3fv(glGetUniformLocation(this->shader_->get_programID(), "lightColor"), 1, glm::value_ptr(this->lightColor_));

	glm::mat4 model;
	model = compositeModel * glm::translate(this->model_, this->centerPoint_) * rotationMatrix_;
	model = glm::scale(model, this->scaleVector_);

	/*Binding texture*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_);
	glUniform1i(glGetUniformLocation(this->shader_->get_programID(), "Texture0"), 0);

	glUniformMatrix4fv(glGetUniformLocation(this->shader_->get_programID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void LightSource::set_geometry(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
	this->set_vertices(vertices);
	this->set_indices(indices);
}
void LightSource::pass_parameters_to_shader(const ShaderProgram& shader, int index) {
	unsigned int i = 0;
	glm::mat4 m = glm::translate(this->model_, this->centerPoint_);
	glm::vec3 test = glm::vec3(m[3][0], m[3][1], m[3][2]);
	std::string arg = ("pointLights[" + std::to_string(index) + rights[i]);
	glUniform3fv(glGetUniformLocation(shader.get_programID(), arg.c_str()), 1, glm::value_ptr(test));

	arg = ("pointLights[" + std::to_string(index) + rights[i+1]);
	glUniform3fv(glGetUniformLocation(shader.get_programID(), arg.c_str()), 1, glm::value_ptr(lightColor_));

	arg = ("pointLights[" + std::to_string(index) + rights[i + 2]);
	glUniform1f(glGetUniformLocation(shader.get_programID(), arg.c_str()), ambientStrength_);

	arg = ("pointLights[" + std::to_string(index) + rights[i + 3]);
	glUniform1f(glGetUniformLocation(shader.get_programID(), arg.c_str()), diffuseStrength_);

	arg = ("pointLights[" + std::to_string(index) + rights[i + 4]);
	glUniform1f(glGetUniformLocation(shader.get_programID(), arg.c_str()), specularStrength_);

	arg = ("pointLights[" + std::to_string(index) + rights[i + 5]);
	glUniform1f(glGetUniformLocation(shader.get_programID(), arg.c_str()), constant_);

	arg = ("pointLights[" + std::to_string(index) + rights[i + 6]);
	glUniform1f(glGetUniformLocation(shader.get_programID(), arg.c_str()), linear_);

	arg = ("pointLights[" + std::to_string(index) + rights[i + 7]);
	glUniform1f(glGetUniformLocation(shader.get_programID(), arg.c_str()), quadratic_);
}

/*------------------------------DirectLight-------------------------*/
DirectLight::DirectLight(
	const glm::vec3& centerPoint,
	const glm::vec3& direction,
	const glm::vec3& lightColor,
	const float ambientStrength,
	const float diffuseStrength,
	const float specularStrength,
	const ShaderProgram* shader) :
		Object3D(centerPoint, glm::vec3(1.0, 1.0, 1.0), shader),
		direction_(direction),
		lightColor_(lightColor), 
		ambientStrength_(ambientStrength), 
		diffuseStrength_(diffuseStrength), 
		specularStrength_(specularStrength) {}

void DirectLight::pass_parameters_to_shader(const ShaderProgram& shader) {
	glUniform3fv(glGetUniformLocation(shader.get_programID(), "dirLight.direction"), 1, glm::value_ptr(direction_));
	glUniform3fv(glGetUniformLocation(shader.get_programID(), "dirLight.lightColor"), 1, glm::value_ptr(lightColor_));
	glUniform1f(glGetUniformLocation(shader.get_programID(), "dirLight.ambientStrength"), ambientStrength_);
	glUniform1f(glGetUniformLocation(shader.get_programID(), "dirLight.diffuseStrength"), diffuseStrength_);
	glUniform1f(glGetUniformLocation(shader.get_programID(), "dirLight.specularStrength"), specularStrength_);
	glUniform1f(glGetUniformLocation(shader.get_programID(), "dirLight.specularStrength"), specularStrength_);
}