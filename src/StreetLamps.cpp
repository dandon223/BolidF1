#include "include/StreetLamps.h"

StreetLamps::StreetLamps(const glm::vec3& center_point, const glm::vec3& scale_vector, const ShaderProgram* basic_shader, const ShaderProgram* light_shader, std::vector<LightSource*>& point_lights):
	Model(center_point, scale_vector) {
	for (int i = -1; i <= 1; ++i) {

	}
}

void StreetLamps::draw(float bolid_center_z, glm::mat4&)
{
}
