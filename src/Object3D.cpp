#include "include/Object3D.h"


Object3D::Object3D() : VAO(0), VBO(0), EBO(0), centerPoint_(glm::vec3(0.0f, 0.0f, 0.0f)) {}
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
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void Object3D::translate(const glm::vec3 &centerPoint) {
	
}
void Object3D::scale(float newScale) {
	
}

Cube::Cube(const ShaderProgram& shader) {
	centerPoint_[0] = 0.0f;
	centerPoint_[1] = 0.0f;
	centerPoint_[2] = 0.0f;
	//this->shader_ = std::make_shared<ShaderProgram>(shader);

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
Cube::~Cube() {};