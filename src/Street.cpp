#include "include\Street.h"

Street::Street(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram* p_shader):
	Model(centerPoint, scaleVector) {
	GLuint texture_id = LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/road.png");
	for (int i = -9; i < 10; ++i) {
		RoadSegment* road_segment = new RoadSegment(texture_id, p_shader);
		road_segment->translate(glm::vec3(0.0, 0.0, i * 12.0));
		this->add(road_segment);
	}
}
