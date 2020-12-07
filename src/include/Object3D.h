#ifndef OBJECT3D_H
#define OBJECT3D_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include "include/shprogram.h"

/*ToDo
2) Popraw wskazniki na smart_ptr
*/
class BasicObject {
public:
	glm::vec3 centerPoint_;
	glm::vec3 scaleVector_;

	BasicObject(const glm::vec3&, const glm::vec3&);
	virtual ~BasicObject() {}
	virtual void bind_buffers() = 0;
	virtual void free_buffers() = 0;
	virtual void draw(glm::mat4&) = 0;

	virtual void translate(const glm::vec3&) = 0;
	virtual void rotate(float, const glm::vec3&) = 0;
	virtual void rotate(float, const glm::vec3&, const glm::vec3&) = 0;
	virtual void scale(const glm::vec3&) = 0;
};

class Object3D : public BasicObject {
private:
	GLuint VAO, VBO, EBO;
	glm::mat4 model_;
	glm::mat4 rotationMatrix_;
	
public:
	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;

	const ShaderProgram* shader_;
	GLuint texture_;

	Object3D(const glm::vec3&, const glm::vec3&,const ShaderProgram*);
	virtual ~Object3D();
	virtual void bind_buffers();
	virtual void free_buffers();
	virtual void draw(glm::mat4& = glm::mat4());

	virtual void translate(const glm::vec3&);
	virtual void rotate(float, const glm::vec3&);
	virtual void rotate(float, const glm::vec3&, const glm::vec3&);
	virtual void scale(const glm::vec3&);

	void set_geometry(const std::vector<GLfloat>&, const std::vector<GLuint>&);
	void set_vertices(const std::vector<GLfloat>&);
	void set_indices(const std::vector<GLuint>&);
	void set_color(const glm::vec3&);
	bool set_shader(ShaderProgram*);
	void set_texture(GLuint);
};
#endif // !OBJECT3D_H

