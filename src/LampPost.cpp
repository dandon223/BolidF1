/**
* Author: Konrad Bratosiewicz
* Lamp post implementation
**/

#include "include\LampPost.h"

LampPost::LampPost(const ShaderProgram *basic_shader, const ShaderProgram *light_shader, std::vector<LightSource*>& point_lights):
	Model(glm::vec3(-8.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0))
{
	Object3D* post_base = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1, 3.0, 0.1), basic_shader);
	post_base->translate(glm::vec3(0.0, 2.0, 0.0));
	post_base->set_geometry(CUBE_VERTICES, CUBE_INDICES);
	post_base->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.png"));
	add(post_base);
	bind_buffers();
}
