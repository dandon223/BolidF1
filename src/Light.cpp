#include "include/Light.h"

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
void LightSource::pass_parameters_to_shader(ShaderProgram* shader) {
	glUniform3fv(glGetUniformLocation(shader->get_programID(), "PLight.position"), 1, glm::value_ptr(centerPoint_));
	glUniform3fv(glGetUniformLocation(shader->get_programID(), "PLight.lightColor"), 1, glm::value_ptr(lightColor_));
	glUniform1f(glGetUniformLocation(shader->get_programID(), "PLight.ambientStrength"), ambientStrength_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "PLight.diffuseStrength"), diffuseStrength_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "PLight.specularStrength"), specularStrength_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "PLight.constant"),	constant_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "PLight.linear"),		linear_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "PLight.quadratic"),	quadratic_);
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

void DirectLight::pass_parameters_to_shader(ShaderProgram* shader) {
	glUniform3fv(glGetUniformLocation(shader->get_programID(), "light.direction"), 1, glm::value_ptr(direction_));
	glUniform3fv(glGetUniformLocation(shader->get_programID(), "light.lightColor"), 1, glm::value_ptr(lightColor_));
	glUniform1f(glGetUniformLocation(shader->get_programID(), "light.ambientStrength"), ambientStrength_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "light.diffuseStrength"), diffuseStrength_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "light.specularStrength"), specularStrength_);
	glUniform1f(glGetUniformLocation(shader->get_programID(), "light.specularStrength"), specularStrength_);
}