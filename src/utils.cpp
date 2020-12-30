#include "include/utils.h"

std::ostream& operator<<(std::ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			std::cout << mx[row][col] << ' ';
		std::cout << std::endl;
	}
	return os;
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

glm::vec3 calculate_normal_vector(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
	glm::vec3 A = b - a;
	glm::vec3 B = c - a;
	glm::vec3 result = glm::vec3( A.y * B.z - A.z * B.y, A.x * B.z - A.z * B.x, A.x * B.y - A.y * B.x );
	return result;
}
GLfloat calculate_vector_length(const glm::vec3& vector_) {
	return (GLfloat)sqrt(vector_.x * vector_.x + vector_.y * vector_.y + vector_.z * vector_.z);
}