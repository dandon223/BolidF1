#include "include\Street.h"

Street::Street(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram* p_shader):
	Model(centerPoint, scaleVector) {
	prev_chunk = 0;
	GLuint texture_id = LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/road.png");
	for (int i = -9; i < 10; ++i) {
		RoadSegment* road_segment = new RoadSegment(texture_id, p_shader);
		road_segment->translate(glm::vec3(0.0, 0.0, i * 12.0));
		this->add(road_segment);
	}
}

void Street::draw(float bolid_center_z, glm::mat4& compositeModel)
{
	int curr_chunk = static_cast<int>(bolid_center_z / 12);
	if (prev_chunk != curr_chunk) {
		this->translate(glm::vec3(0.0, 0.0, (curr_chunk - prev_chunk) * 12.0));
		prev_chunk = curr_chunk;
	}
	glm::mat4 model;
	model = compositeModel * glm::translate(this->model_, this->centerPoint_) * rotationMatrix_;

	for (auto& object : this->objectsVector_) {
		object->draw(model);
	}
}
