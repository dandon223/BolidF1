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
		delete object;
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