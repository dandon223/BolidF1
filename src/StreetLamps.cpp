#include "include/StreetLamps.h"

StreetLamps::StreetLamps(const glm::vec3& center_point, const glm::vec3& scale_vector, const ShaderProgram* basic_shader, const ShaderProgram* light_shader, std::vector<LightSource*>& point_lights):
	Model(center_point, scale_vector) {
	for (int i = -1; i <= 1; ++i) {
		LampPost* lamp_post = new LampPost(basic_shader, light_shader, point_lights);
		lamp_post->translate(glm::vec3(-8.0, 0.0, 60.0 * i));
		add(lamp_post);
	}
}
