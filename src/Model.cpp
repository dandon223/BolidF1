#include "include/Model.h"

Model::Model(const glm::vec3& centerPoint, const glm::vec3& scaleVector) : BasicObject(centerPoint, scaleVector) {}
Model::~Model() {
	this->free_buffers();
}
bool Model::add(BasicObject* objectToAdd) {
	try {
		this->objectsVector_.push_back(objectToAdd);
	}
	catch (...) {
		return false;
	}
	return true;
}
bool Model::remove(unsigned int index) {
	if (index < this->objectsVector_.size()) {
		this->objectsVector_.erase(this->objectsVector_.begin() + index);
		return true;
	}
	else return false;
}
BasicObject* Model::getChild(unsigned int index) {
	if (index < this->objectsVector_.size()) {
		return this->objectsVector_[index];
	}
	else return nullptr;
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
void Model::draw(glm::mat4& compositeModel) {

	glm::mat4 model;
	model = compositeModel * glm::translate(this->model_, this->centerPoint_) * rotationMatrix_;

	for (auto& object : this->objectsVector_) {
		object->draw(model);
	}
}
void Model::translate(const glm::vec3& translateVector) {
	this->centerPoint_ += translateVector;
}
void Model::rotate(float angle, const glm::vec3& rotationAxis) {
	glm::mat4 model;
	this->rotationMatrix_ = glm::rotate(model, glm::radians(angle), rotationAxis) * rotationMatrix_;
}
void Model::rotate(float angle, const glm::vec3& rotationAxis, const glm::vec3& fixedPoint) {
	this->model_ = glm::translate(this->model_, fixedPoint);
	this->model_ = glm::rotate(this->model_, glm::radians(angle), rotationAxis);
	this->model_ = glm::translate(this->model_, -fixedPoint);
}
void Model::scale(const glm::vec3& scaleVector) {
	this->scaleVector_ += scaleVector;

	for (auto& object : this->objectsVector_) {
		object->scale(scaleVector);
	}
}

Cube::Cube(const ShaderProgram* shader) : Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), shader) {
	shader_ = shader;

	this->vertices_ = {
		// coordinates			// texture
		0.5f,  0.5f,  -0.5f,		1.0f,  0.0f,	//0
		-0.5f,  0.5f,  -0.5f,		0.0f,  0.0f,	//1
		-0.5f, -0.5f,  -0.5f,		0.0f,  1.0f,	//2
		0.5f, -0.5f,  -0.5f,		1.0f,  1.0f,	//3

		-0.5f, -0.5f,  0.5f,		0.0f,  0.0f,	//4
		-0.5f,  0.5f,  0.5f,		0.0f,  1.0f,	//5
		0.5f,  0.5f,  0.5f,			1.0f,  1.0f,	//6
		0.5f, -0.5f,  0.5f,			1.0f,  0.0f,	//7

		-0.5f, -0.5f,  -0.5f,		0.0f,  0.0f,	//8
		-0.5f, -0.5f,  0.5f,		0.0f,  1.0f,	//9
		0.5f, -0.5f,  0.5f,			1.0f,  1.0f,	//10
		0.5f, -0.5f,  -0.5f,		1.0f,  0.0f,	//11

		-0.5f,  0.5f,  0.5f,		0.0f,  0.0f,	//12
		-0.5f,  0.5f,  -0.5f,		0.0f,  1.0f,	//13
		0.5f,  0.5f,  -0.5f,		1.0f,  1.0f,	//14
		0.5f,  0.5f,  0.5f,			1.0f,  0.0f,	//15

		-0.5f, -0.5f,  -0.5f,		0.0f,  0.0f,	//16
		-0.5f,  0.5f,  -0.5f,		0.0f,  1.0f,	//17
		-0.5f, -0.5f,  0.5f,		1.0f,  0.0f,	//18
		-0.5f,  0.5f,  0.5f,		1.0f,  1.0f,	//19

		0.5f, -0.5f,  -0.5f,		1.0f,  0.0f,	//20
		0.5f, -0.5f,  0.5f,			0.0f,  0.0f,	//21
		0.5f,  0.5f,  0.5f,			0.0f,  1.0f,	//22
		0.5f,  0.5f,  -0.5f,		1.0f,  1.0f		//23

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

Cylinder::Cylinder(unsigned int hight, unsigned int sides, const glm::vec3& centerPoint, const ShaderProgram* shader) : Object3D(centerPoint, glm::vec3(1.0, 1.0, 1.0), shader) {
	float angle = 360.0 / sides;
	int i = 0;
	for (i = 0; i < sides; ++i) {

	}

}