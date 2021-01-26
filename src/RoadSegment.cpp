/**
 * Author: Konrad Bratosiewicz
 * Road segment implementation
 **/

#include "include/RoadSegment.h"

RoadSegment::RoadSegment(ShaderProgram* p_shader) :
    Object3D(glm::vec3(0.0, -0.95, 0.0), glm::vec3(1.0, 1.0, 1.0), p_shader) {

    this->set_geometry(VERTICES, INDICES);
    this->rotate(-90.0, glm::vec3(1.0, 0.0, 0.0));
    this->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/road.png"));
    this->bind_buffers();
}