#include "include/Model.h"

Model::Model(const glm::vec3& centerPoint, const glm::vec3& scaleVector) : BasicObject(centerPoint, scaleVector) {}
Model::~Model() {
	this->free_buffers();
}
bool Model::add(BasicObject* objectToAdd) {
	//std::unique_ptr<BasicObject> newObject = std::make_unique<BasicObject>(objectToAdd);
	this->objectsVector_.push_back(objectToAdd);
	//this->objectsVector_.push_back(newObject);
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