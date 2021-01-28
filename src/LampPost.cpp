/**
* Author: Konrad Bratosiewicz
* Lamp post implementation
**/

#include "include\LampPost.h"

LampPost::LampPost(const ShaderProgram *basic_shader, const ShaderProgram *light_shader, std::vector<LightSource*>& point_lights):
	Model(glm::vec3(-8.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0))
{
	Object3D* post_base = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 5.0, 0.1), basic_shader);
	post_base->translate(glm::vec3(0.0, 4.0, 0.0));
	post_base->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	post_base->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.png"));
	add(post_base);

	Object3D* post_bar = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.07, 1.3, 0.07), basic_shader);
	post_bar->rotate(-80.0, glm::vec3(0.0, 0.0, 1.0));
	post_bar->translate(glm::vec3(1.0, 9.0, 0.0));
	post_bar->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	post_bar->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.png"));
	add(post_bar);

	Object3D* light_case = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 0.5, 0.25), basic_shader);
	light_case->rotate(-80.0, glm::vec3(0.0, 0.0, 1.0));
	light_case->translate(glm::vec3(2.0, 9.18, 0.0));
	light_case->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	light_case->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.png"));
	add(light_case);

	LightSource *light = create_pointLight(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 0.2, 1.0, 1.0, 1.0, 0.009, 0.0032, *light_shader, point_lights);
	light->rotate(-80.0, glm::vec3(0.0, 0.0, 1.0));
	light->scale(glm::vec3(-0.96, -0.6, -0.8));
	light->translate(glm::vec3(-5.95, 9.05, 0.0));

	bind_buffers();
}
