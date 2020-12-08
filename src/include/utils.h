#ifndef UTILS_H
#define UTILS_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream&, const glm::mat4&);

GLuint LoadMipmapTexture(GLuint , const char* );

#endif // !UTILS_H

