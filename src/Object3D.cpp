#include "include/Object3D.h"
#include "include/utils.h"
#include <cmath>

BasicObject::BasicObject(const glm::vec3& centerPoint, const glm::vec3& scaleVector) : centerPoint_(centerPoint), scaleVector_(scaleVector) {}

Object3D::Object3D(const glm::vec3& centerPoint, const glm::vec3& scaleVector,const ShaderProgram* shader) : BasicObject(centerPoint,scaleVector), VAO(0), VBO(0), EBO(0), model_(glm::mat4(1.0f)), shader_(shader), texture_(0) {}
Object3D::~Object3D() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}
void Object3D::bind_buffers() {
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertices_.size(), this->vertices_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices_.size(), this->indices_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	normals_.clear();
}
void Object3D::free_buffers() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}
void Object3D::draw(glm::mat4& compositeModel) {
	glm::mat4 model;
	model = compositeModel * glm::translate(this->model_, this->centerPoint_) * rotationMatrix_;
	model = glm::scale(model, this->scaleVector_);

	/*Binding texture*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_);

	//filtrowanie anizotropowe
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	glUniform1i(glGetUniformLocation(this->shader_->get_programID(), "Texture0"), 0);

	glUniformMatrix4fv(glGetUniformLocation(this->shader_->get_programID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

	/*glUniform3fv(glGetUniformLocation(this->shader_->get_programID(), "material.ambientColor"), 1, glm::value_ptr(materialParam_[0]));
	glUniform3fv(glGetUniformLocation(this->shader_->get_programID(), "material.diffuseColor"), 1, glm::value_ptr(materialParam_[1]));
	glUniform3fv(glGetUniformLocation(this->shader_->get_programID(), "material.specularColor"), 1, glm::value_ptr(materialParam_[2]));
	glUniform1f(glGetUniformLocation(this->shader_->get_programID(), "material.shininess"), shininess_);*/

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void Object3D::translate(const glm::vec3 &translateVector) {
	this->centerPoint_ += translateVector;
}
void Object3D::rotate(float angle, const glm::vec3& rotationAxis) {
	glm::mat4 model;
	this->rotationMatrix_ = glm::rotate(model, glm::radians(angle), rotationAxis) * rotationMatrix_;
}
void Object3D::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	this->model_ = glm::translate(this->model_, fixedPoint);
	this->model_ = glm::rotate(this->model_, glm::radians(angle), rotationAxis);
	this->model_ = glm::translate(this->model_, -fixedPoint);
}
void Object3D::scale(const glm::vec3& scaleVector) {
	this->scaleVector_ += scaleVector;
}
void Object3D::set_geometry(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
	this->set_vertices(vertices);
	this->set_indices(indices);
	this->calculate_normals();
}
void Object3D::set_vertices(const std::vector<GLfloat>& vertices) {
	if (vertices.size() > 0) {
		this->vertices_ = vertices;
	}
}
void Object3D::set_indices(const std::vector<GLuint>& indices) {
	if (indices.size() > 0) {
		this->indices_ = indices;
	}
}
void Object3D::calculate_normals() {
	glm::vec3 a, b, c, result;
	for (int i = 0; i < this->indices_.size(); i = i + 3) {
		a = glm::vec3(this->vertices_[5*indices_[i]], this->vertices_[5*indices_[i] + 1], this->vertices_[5*indices_[i] + 2]);
		b = glm::vec3(this->vertices_[5*indices_[i + 1]], this->vertices_[5*indices_[i + 1] + 1], this->vertices_[5*indices_[i + 1] + 2]);
		c = glm::vec3(this->vertices_[5*indices_[i + 2]], this->vertices_[5*indices_[i + 2] + 1], this->vertices_[5*indices_[i + 2] + 2]);
		
		result = calculate_normal_vector(c, b, a);

		this->normals_.push_back(result.x);
		this->normals_.push_back(result.y);
		this->normals_.push_back(result.z);
	}
	std::vector<GLfloat> tmp;
	int i = 0, n = 0, counter = 0;
	for (i = 0 ; i < this->vertices_.size()/5; ++i){
		for(int j = 0; j < 3; ++j){
			tmp.push_back(vertices_[5*i + j]);
		}
		for(int k = 0; k < 3; ++k){
			tmp.push_back(normals_[3*n + k]);
		}
		for(int t = 0; t < 2; ++t){
			tmp.push_back(vertices_[5*i + 3 + t]);
		}
		++counter;
		if(counter == 3){
			counter = 0;
			++n;
		}
	}
	vertices_ = tmp;
}
bool Object3D::set_shader(ShaderProgram* shader) {
	if (shader != nullptr) {
		this->shader_ = shader;
		return true;
	}
	return false;
}
void Object3D::set_texture(GLuint texture) {
	this->texture_ = texture;
}
void Object3D::set_material(const glm::vec3& ambientColor, const glm::vec3& diffuseColor, const glm::vec3& specularColor, float shininess) {
	materialParam_[0] = ambientColor;
	materialParam_[1] = diffuseColor;
	materialParam_[2] = specularColor;
	shininess_ = shininess;
}