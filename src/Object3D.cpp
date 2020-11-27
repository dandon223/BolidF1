#include "include/Object3D.h"
#include "include/utils.h"

BasicObject::BasicObject(const glm::vec3& centerPoint, const glm::vec3& translateVector, const glm::vec3& scaleVector) : centerPoint_(centerPoint), translateVector_(translateVector), scaleVector_(scaleVector) {}

Object3D::Object3D(const glm::vec3& centerPoint, const glm::vec3& translateVector, const glm::vec3& scaleVector,const ShaderProgram* shader) : BasicObject(centerPoint,translateVector,scaleVector), VAO(0), VBO(0), EBO(0), model_(glm::mat4(1.0f)), shader_(shader), texture_(0) {}
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
}
void Object3D::free_buffers() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}
void Object3D::draw() {
	glm::mat4 model;
	model = glm::translate(this->model_, this->centerPoint_);
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
void Object3D::translate(const glm::vec3 &translateVector) {
	this->centerPoint_ += translateVector;
}
void Object3D::rotate(float angle, const glm::vec3& rotationAxis) {
	this->model_ = glm::rotate(this->model_, glm::radians(angle), rotationAxis);
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


//ToDo
//1. Ogarnij klase kompozytu
Model::Model(const glm::vec3& centerPoint, const glm::vec3& translateVector, const glm::vec3& scaleVector) : BasicObject(centerPoint, translateVector, scaleVector) {}
Model::~Model() {
	this->free_buffers();
}
bool Model::add(BasicObject* objectToAdd) {
	//std::unique_ptr<BasicObject *> newObject = std::make_unique<BasicObject *>(objectToAdd);
	this->objectsVector_.push_back(objectToAdd);
	return true;
}
bool Model::remove(unsigned int index) {
	if (index < this->objectsVector_.size()) {
		this->objectsVector_.erase(this->objectsVector_.begin() + index);
		return true;
	}
	else return false;
}
void Model::bind_buffers() {
	for (auto& object : this->objectsVector_) {
		object->bind_buffers();
	}
}
void Model::free_buffers() {
	for (auto& object : this->objectsVector_) {
		object->free_buffers();
	}
}
void Model::draw() {
	for (auto& object : this->objectsVector_) {
		object->draw();
	}
}
void Model::translate(const glm::vec3& translateVector) {
	this->centerPoint_ += translateVector;
	for (auto& object : this->objectsVector_) {
		object->translate(translateVector);
	}
}
void Model::rotate(float angle, const glm::vec3& rotationAxis) {
	for (auto& object : this->objectsVector_) {
		object->rotate(angle, rotationAxis, this->centerPoint_);
	}
}
void Model::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	for (auto& object : this->objectsVector_) {
		object->rotate(angle, rotationAxis, fixedPoint);
	}
}
void Model::scale(const glm::vec3& scaleVector) {
	for (auto& object : this->objectsVector_) {
		object->scale(scaleVector);
	}
}


Cube::Cube(const ShaderProgram* shader) : Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), shader) {
	shader_ = shader;

	this->vertices_ = {
		// coordinates			// color			// texture
			0.5f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//0
			-0.5f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//1
			-0.5f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//2
			0.5f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//3

			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//4
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//5
			0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//6
			0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//7

			-0.5f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//8
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//9
			0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//10
			0.5f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//11

			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//12
			-0.5f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//13
			0.5f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//14
			0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//15

			-0.5f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//16
			-0.5f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//17
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//18
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f,  1.0f,	//19

			0.5f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//20
			0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//21
			0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//22
			0.5f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f		//23

	};
	this->indices_ = {
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			18, 17, 19,
			20, 21, 22,
			20, 22, 23

	};
}
Cube::~Cube() {};