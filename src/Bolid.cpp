#include "include/Bolid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <cmath>
#include "include/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Bolid::Bolid(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram* shader) : Model(centerPoint, scaleVector)
{
	Kadlub* kadlub = new Kadlub(centerPoint, scaleVector, shader);
	PrzedniSpoiler* przedniSpoiler = new PrzedniSpoiler(centerPoint, scaleVector, shader);
	TylnySpoiler* tylnySpoiler = new TylnySpoiler(centerPoint, scaleVector, shader);
	Kolo* tylnaOs[2];
	tylnaOs[0] = new Kolo(centerPoint, scaleVector, shader, 0.4f, 20, 0.3f, 'L', 'T');
	tylnaOs[1] = new Kolo(centerPoint, scaleVector, shader, 0.4f, 20, 0.3f, 'P', 'T');
	Kolo* przedniaOs[2];
	przedniaOs[0] = new Kolo(centerPoint, scaleVector, shader, 0.4f, 20, 0.3f, 'L', 'P');
	przedniaOs[1] = new Kolo(centerPoint, scaleVector, shader, 0.4f, 20, 0.3f, 'P', 'P');
	Zawieszenie* zawieszenie = new Zawieszenie(centerPoint, scaleVector, shader);
	kadlub = new Kadlub(centerPoint, scaleVector, shader);
	przedniSpoiler = new PrzedniSpoiler(centerPoint, scaleVector, shader);
	tylnySpoiler = new TylnySpoiler(centerPoint, scaleVector, shader);
	tylnySpoiler->translate(glm::vec3(0.0f, 2.5f, -1.7f));
	kadlub->scale( glm::vec3(1.0f, 1.0f, 1.0f));
	kadlub->translate(glm::vec3(0.0f, 1.5f, 0.0f));
	kadlub->rotate(-90, glm::vec3(1.0f, 0.0f, 0.0f));
	przedniSpoiler->translate(glm::vec3(0.0, 1.3, 1.9));
	przedniSpoiler->rotate(180, glm::vec3(0.0, 1.0, 0.0));

	this->add(tylnySpoiler);
	this->add(przedniSpoiler);
	this->add(kadlub);
	this->add(zawieszenie);
	for (int i = 0; i < 2; ++i) {
		this->add(tylnaOs[i]);
		this->add(przedniaOs[i]);
	}
	this->bind_buffers();

}
void Bolid::setProjectionView(glm::mat4 p, glm::mat4 v) {}
void Bolid::shaderUse() {}
// check for potential camera movement user input
void Bolid::processKeyboardInput(GLFWwindow* window) {
	double curr_frame_time = glfwGetTime();
	delta_time = delta_time +(curr_frame_time - prev_frame_time);
	prev_frame_time = curr_frame_time;
	//std::cout << delta_time << std::endl;
	//float bolidSpeed = MOVEMENT_SPEED * static_cast<float>(delta_time);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && speed==0 && delta_time > 0.1) {
		delta_time = 0;
		if (inReverse)
			inReverse = false;
		else
			inReverse = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (!inReverse) {
			speed += 0.3*log(speed/10 + SPEED_RATE);
			wheel_speed = 10 * speed + 1;
			if (current_degree == MAX_DEGREE || current_degree == MIN_DEGREE) wheel_speed = 6.0f;
			for (int i = 0; i < 3; ++i) {
				static_cast<Model*>(getChild(4))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(5))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(6))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(7))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (speed > MAX_SPEED)
				speed = MAX_SPEED;
		}
		else {
			speed -= 0.3*log(speed/10 + SPEED_RATE);
			wheel_speed = 10 * speed - 1;
			for (int i = 0; i < 3; ++i) {
				static_cast<Model*>(getChild(4))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(5))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(6))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(7))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (speed < MAX_SPEED_REVERSE)
				speed = MAX_SPEED_REVERSE;
		}
			
	}
	else {
		if (speed > 0) {
			speed -= 2*speed*(STOP_SPEED) + 0.0005f;
			wheel_speed = 10 * speed + 1.0f;
			for (int i = 0; i < 3; ++i) {
				static_cast<Model*>(getChild(4))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(5))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(6))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(7))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (speed < 0)
				speed = 0;
		}
		else if(speed < 0) {
			speed += 2*speed*(STOP_SPEED) + 0.0005f;
			wheel_speed = 10 * speed - 1.0f;
			for (int i = 0; i < 3; ++i) {
				static_cast<Model*>(getChild(4))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(5))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(6))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
				static_cast<Model*>(getChild(7))->getChild(i)->rotate(wheel_speed, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			if (speed > 0)
				speed = 0;
		}
		
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (!inReverse) {
			speed -= 0.6*log(speed/10 + SPEED_RATE);
			if (speed < 0)
				speed = 0;
		}
		else {
			speed += log(SPEED_RATE - speed/5);
			if (speed > 0)
				speed = 0;
		}
		
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (speed != 0) {
			if (!inReverse) {
				rotate(rotationAngle, glm::vec3(0.0, 1.0, 0.0));
				rotation_position += 1;
			}
			else {
				rotate(rotationAngle, glm::vec3(0.0, -1.0, 0.0));
				rotation_position -= 1;
			}
		}
		if (current_degree < MAX_DEGREE) {
			for (int i = 0; i < 3; ++i) {
				static_cast<Model*>(getChild(5))->getChild(i)->rotate(rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f), static_cast<Model*>(getChild(5))->getChild(1)->centerPoint_);
				static_cast<Model*>(getChild(7))->getChild(i)->rotate(rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f), static_cast<Model*>(getChild(7))->getChild(1)->centerPoint_);
			}
			current_degree += 1;
		}
		rotation_position = rotation_position % 360;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (speed != 0) {
			if (!inReverse) {
				rotate(rotationAngle, glm::vec3(0.0, -1.0, 0.0));
				rotation_position -= 1;
			}
			else {
				rotate(rotationAngle, glm::vec3(0.0, 1.0, 0.0));
				rotation_position += 1;
			}
			
		}
		if (current_degree > MIN_DEGREE) {
			for (int i = 0; i < 3; ++i) {
				static_cast<Model*>(getChild(5))->getChild(i)->rotate(-rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f), static_cast<Model*>(getChild(5))->getChild(1)->centerPoint_);
				static_cast<Model*>(getChild(7))->getChild(i)->rotate(-rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f), static_cast<Model*>(getChild(7))->getChild(1)->centerPoint_);
			}
			current_degree -= 1;
		}
		rotation_position = rotation_position % 360;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS) {
		for (int i = 0; i < 3; ++i) {
			static_cast<Model*>(getChild(5))->getChild(i)->rotate(-current_degree, glm::vec3(0.0f, 1.0f, 0.0f), static_cast<Model*>(getChild(5))->getChild(1)->centerPoint_);
			static_cast<Model*>(getChild(7))->getChild(i)->rotate(-current_degree, glm::vec3(0.0f, 1.0f, 0.0f), static_cast<Model*>(getChild(7))->getChild(1)->centerPoint_);
		}
		current_degree = 0;
	}

	float x = sin((float)rotation_position * PI / 180.0) * speed;
	float z = cos((float)rotation_position * PI / 180.0) * speed;
	translate(glm::vec3(x, 0.0, z));
}
int Bolid::getRotationPosition() {
	return rotation_position;
}
bool Bolid::isInReverse() {
	return inReverse;
}

