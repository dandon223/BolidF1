/**
* Author: Konrad Bratosiewicz
* Lamp post implementation
**/

#include "include\LampPost.h"

LampPost::LampPost(const ShaderProgram *basic_shader, const ShaderProgram *light_shader, std::vector<LightSource*>& point_lights):
	Model(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0))
{
	GLuint texture_id = LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/lamp_post.png");
	
	Object3D* base = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 5.0, 0.1), basic_shader);
	base->translate(glm::vec3(0.0, 4.0, 0.0));
	base->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	base->set_texture(texture_id);
	add(base);

	Object3D* bar = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.07, 1.3, 0.07), basic_shader);
	bar->rotate(-80.0, glm::vec3(0.0, 0.0, 1.0));
	bar->translate(glm::vec3(1.0, 9.0, 0.0));
	bar->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	bar->set_texture(texture_id);
	add(bar);

	Object3D* light_case = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 0.5, 0.25), basic_shader);
	light_case->rotate(-80.0, glm::vec3(0.0, 0.0, 1.0));
	light_case->translate(glm::vec3(2.0, 9.18, 0.0));
	light_case->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	light_case->set_texture(texture_id);
	add(light_case);

	light_ = create_pointLight(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 1.0), 0.0, 0.8, 1.0, 1.0, 0.027, 0.0028, *light_shader, point_lights);
	light_->rotate(-80.0, glm::vec3(0.0, 0.0, 1.0));
	light_->scale(glm::vec3(-0.96, -0.6, -0.8));
	light_->translate(glm::vec3(2.05, 9.05, 0.0));

	bind_buffers();
}

void LampPost::translate(const glm::vec3& translate_vector)
{
	this->centerPoint_ += translate_vector;
	light_->translate(translate_vector);
}

void LampPost::rotate(float angle, const glm::vec3& rotation_axis) {
	light_->translate(glm::vec3(2*(this->centerPoint_.x - light_->centerPoint_.x), 0.0, 0.0));
	light_->rotate(angle, rotation_axis);
	glm::mat4 model;
	this->rotationMatrix_ = glm::rotate(model, glm::radians(angle), rotation_axis) * rotationMatrix_;
}
