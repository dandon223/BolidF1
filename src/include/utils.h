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
#include <vector>
#include "shprogram.h"
#include "Light.h"

std::ostream& operator<<(std::ostream&, const glm::mat4&);

GLuint LoadMipmapTexture(GLuint , const char* );
glm::vec3 calculate_normal_vector(const glm::vec3&, const glm::vec3&, const glm::vec3&);
GLfloat calculate_vector_length(const glm::vec3&);
void pass_proj_view(const glm::mat4&, const glm::mat4&, const ShaderProgram& shader);
LightSource* create_pointLight(const glm::vec3&, const glm::vec3&, const float, const float, const float, const float, const float, const float, const ShaderProgram&, std::vector<LightSource*>&);

#endif // !UTILS_H

