#include "include/StreetLamps.h"

StreetLamps::StreetLamps(const glm::vec3& center_point, const glm::vec3& scale_vector, const ShaderProgram* basic_shader, const ShaderProgram* light_shader, std::vector<LightSource*>& point_lights):
	Model(center_point, scale_vector) {
	prev_chunk_ = 0;
	LampPost* lamp_post;
	for (int i = -2; i <= 2; ++i) {
		lamp_post = new LampPost(basic_shader, light_shader, point_lights);
		lamp_post->translate(glm::vec3(-8.0, 0.0, 60.0 * i));
		add(lamp_post);

		lamp_post = new LampPost(basic_shader, light_shader, point_lights);
		lamp_post->translate(glm::vec3(8.0, 0.0, 60.0 * i));
		lamp_post->rotate(180.0, glm::vec3(0.0, 1.0, 0.0));
		add(lamp_post);
	}
}

void StreetLamps::draw(float bolid_center_z, glm::mat4& composite_model)
{
	int curr_chunk = static_cast<int>(bolid_center_z / 60);
	if (prev_chunk_ != curr_chunk) {
		this->translate(glm::vec3(0.0, 0.0, (curr_chunk - prev_chunk_) * 60.0));
		prev_chunk_ = curr_chunk;
	}
	glm::mat4 model;
	model = composite_model * glm::translate(this->model_, this->centerPoint_) * rotationMatrix_;

	for (auto& object : this->objectsVector_) {
		object->draw(model);
	}
}

void StreetLamps::translate(const glm::vec3 &translate_vector)
{
	bool right = true;
	for (auto & a : objectsVector_) {
		a->translate(translate_vector);
	}
}
