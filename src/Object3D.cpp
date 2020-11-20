#include "include/Object3D.h"


Object3D::Object3D() {}
Object3D::~Object3D() {}
void Object3D::translate(const glm::vec3 &centerPoint) {
	if (!this->vertices_.empty()) {
		int i;
		for (i = 0; i < 3; ++i) {
			this->centerPoint_[i] = centerPoint[i];
		}
		i = 0;
		while(i < this->vertices_.size()) {
			this->vertices_[i] += this->centerPoint_[0];
			this->vertices_[i + 1] += this->centerPoint_[1];
			this->vertices_[i + 2] += this->centerPoint_[2];
			i += 8;
		}
	}
}
void Object3D::scale(float newScale) {
	if (!this->vertices_.empty()) {
		int i = 0;
		while (i < this->vertices_.size()) {
			this->vertices_[i] *= newScale;
			this->vertices_[i + 1] *= newScale;
			this->vertices_[i + 2] *= newScale;
			i += 8;
		}
	}
}
void Object3D::draw() {
	//glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}

cube::cube() {
	centerPoint_[0] = 0.0f;
	centerPoint_[1] = 0.0f;
	centerPoint_[2] = 0.0f;

	this->vertices_ = {
		// coordinates			// color			// texture
		-0.5f,  -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//0
		 0.5f,  -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//1
		 0.5f,   0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//2
		-0.5f,   0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//3

		-0.5f,  -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//4
		 0.5f,  -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//5
		 0.5f,   0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//6
		-0.5f,   0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//7
	};
	this->indices_ = {
			0, 1, 2,
			0, 3, 2,
			1, 5, 6,
			1, 6, 2,
			1, 4, 0,
			1, 5, 4,
			2, 7, 3,
			2, 6, 7,
			4, 3, 7,
			4, 0, 3,
			5, 7, 6,
			5, 4, 7
	};
}
cube::~cube() {};