#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);	// global up vector, used as reference for manouvering in scene space

class Camera {
public:
	glm::vec3 position_;	// camera's coordinates
	glm::vec3 front_;		// direction vector
	glm::vec3 up_;
	glm::vec3 right_;

	float yaw_;
	float pitch_;
	float fov_;
	
	// // //
	
	Camera() {
		position_ = INIT_POSITION;
		front_	  = INIT_FRONT;
		up_		  = UP;
		yaw_	  = INIT_YAW;
		pitch_	  = INIT_PITCH;
		fov_	  = INIT_FOV;
	};

	glm::mat4 getViewMatrix();

	void processKeyboardInput(GLFWwindow* window);
	void processMouseMovement(double x_offset, double y_offset);
	void processMouseScroll(double y_offset);
	void setPosition(glm::vec3 pos);
	void setIsInsideBolid(bool b);
	void setRotationPosition(int pos);
	void movementInBolid();

private:
	void updateCameraVectors();

	// // //

	double delta_time, prev_frame_time = 0.0f;
	
	// // //
	
	const glm::vec3 INIT_POSITION = glm::vec3(0.0f, 0.0f, 3.0f);
	const glm::vec3 INIT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);

	const float INIT_YAW = -90.0;
	float MIN_YAW = 60.0;
	float MAX_YAW = 120.0;
	int rotation_position = 0;
	bool rotation_left = false;
	bool rotation_pos_changed = false;
	bool is_inside_bolid = false;

	const float INIT_PITCH = 0.0f;
	const float MAX_PITCH  = 59.9f;
	const float MIN_PITCH  = -59.9f;

	const float INIT_FOV = 45.0f;
	const float MAX_FOV  = 75.0f;
	const float MIN_FOV  = 1.0f;

	const float MOVEMENT_SPEED = 2.4f;

	const double MOUSE_SENSITIVITY = 0.08f;
};