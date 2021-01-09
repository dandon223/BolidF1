#include "include/camera.h"

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::updateCameraVectors() {
	glm::vec3 tmp_front;
	tmp_front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	tmp_front.y = sin(glm::radians(pitch_));
	tmp_front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_ = glm::normalize(tmp_front);
	right_ = glm::normalize(glm::cross(front_, UP));
	up_	   = glm::normalize(glm::cross(right_, front_));
}

	// check for potential camera movement user input
void Camera::processKeyboardInput(GLFWwindow* window) {
	double curr_frame_time = glfwGetTime();
	delta_time = curr_frame_time - prev_frame_time;
	prev_frame_time = curr_frame_time;

	float cameraSpeed = MOVEMENT_SPEED * static_cast<float>(delta_time);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position_ += cameraSpeed * front_;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position_ -= cameraSpeed * front_;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position_ -= cameraSpeed * right_;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position_ += cameraSpeed * right_;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)		// straight up
		position_ += cameraSpeed * up_;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)		// straight down
		position_ -= cameraSpeed * up_;
	
}
void Camera::setPosition(glm::vec3 pos) {
	position_ = pos;
};

	// update camera's parameters after user moves their mouse
void Camera::processMouseMovement(double x_offset, double y_offset) {
	x_offset *= MOUSE_SENSITIVITY;
	y_offset *= MOUSE_SENSITIVITY;

	yaw_ = std::fmod((yaw_ + static_cast<float>(x_offset)), 360.0f);
	if (is_inside_bolid ) {
		

		if (rotation_pos_changed &&  rotation_position != 0) {
			rotation_pos_changed = false;
			if (rotation_left) {
				MIN_YAW -= 1;
				MAX_YAW -= 1;
				yaw_ -= 1;
			}
			else {
				MIN_YAW += 1;
				MAX_YAW += 1;
				yaw_ += 1;
			}
		}
		if (MIN_YAW < -359) {
			int x = MIN_YAW / 360;
			MIN_YAW = MIN_YAW - 360 * x;
			MAX_YAW = MIN_YAW + 100;
		}	
		if (MAX_YAW > 359){
			int x = MAX_YAW / 360;
			MAX_YAW = MAX_YAW - 360*x;
			MIN_YAW = MAX_YAW -100;
			
		}
		if (yaw_ > 360 || yaw_ < -360) {
			int x = yaw_ / 360;
			yaw_ = yaw_ - 360 * x;
		}
		if (yaw_ < MIN_YAW) {
			yaw_ = MIN_YAW;
		}
		else if (yaw_ > MAX_YAW) {
			yaw_ = MAX_YAW;
		}
	}
	
	pitch_ += static_cast<float>(y_offset);
	if (pitch_ < MIN_PITCH)
		pitch_ = MIN_PITCH;
	else if (pitch_ > MAX_PITCH)
		pitch_ = MAX_PITCH;
	
	updateCameraVectors();
}
void Camera::setIsInsideBolid(bool b) {
	is_inside_bolid = b;
}
void Camera::movementInBolid() {
	if (rotation_pos_changed &&  rotation_position!=0) {
		rotation_pos_changed = false;
		if (rotation_left) {
			yaw_ -= 1;
			MIN_YAW -= 1;
			MAX_YAW -= 1;
		}
		else {
			yaw_ += 1;
			MIN_YAW += 1;
			MAX_YAW += 1;
		}
		updateCameraVectors();
	}
	

}

	// update camera's parameters after mouse scroll is used
void Camera::processMouseScroll(double y_offset) {
	fov_ -= static_cast<float>(y_offset);
	if (fov_ < MIN_FOV)
		fov_ = MIN_FOV;
	else if (fov_ > MAX_FOV)
		fov_ = MAX_FOV;
}
void Camera::setRotationPosition(int pos) {
	if (rotation_position != pos)
		rotation_pos_changed = true;
		if (rotation_position < pos)
			rotation_left = true;
		else
			rotation_left =false;
		rotation_position = pos;
	
}