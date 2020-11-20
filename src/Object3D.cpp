#include "include/Object3D.h"


Object3D::Object3D() {}
Object3D::~Object3D() {}
void Object3D::draw() {
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}

cube::cube() {
	centerPoint[0] = 0.0f;
	centerPoint[1] = 0.0f;
	centerPoint[2] = 0.0f;

	this->vertices = {
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
	this->indices = {
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