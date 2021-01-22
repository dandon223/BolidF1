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
	Kadlub* kadlub = new Kadlub(centerPoint, scaleVector,shader);
	PrzedniSpoiler* przedniSpoiler = new PrzedniSpoiler(centerPoint, scaleVector, shader);
	TylnySpoiler* tylnySpoiler = new TylnySpoiler(centerPoint, scaleVector, shader);
	Kola* ukladJezdny = new Kola(centerPoint, scaleVector, shader, 0.4f, 20, 0.3f);
	Zawieszenie* zawieszenie = new Zawieszenie(centerPoint, scaleVector, shader);
	kadlub = new Kadlub(centerPoint, scaleVector, shader);
	przedniSpoiler = new PrzedniSpoiler(centerPoint, scaleVector, shader);
	tylnySpoiler = new TylnySpoiler(centerPoint, scaleVector, shader);
	tylnySpoiler->translate(glm::vec3(0.0f, 2.3f, -1.7f));
	kadlub->scale( glm::vec3(1.0f, 1.0f, 1.0f));
	kadlub->translate(glm::vec3(0.0f, 1.5f, 0.0f));
	kadlub->rotate(-90, glm::vec3(1.0f, 0.0f, 0.0f));
	przedniSpoiler->translate(glm::vec3(0.0, 1.3, 1.9));
	przedniSpoiler->rotate(180, glm::vec3(0.0, 1.0, 0.0));

	this->add(tylnySpoiler);
	this->add(przedniSpoiler);
	this->add(kadlub);
	this->add(ukladJezdny);
	this->add(zawieszenie);
	this->bind_buffers();

}
void Bolid::setProjectionView(glm::mat4 p, glm::mat4 v) {}
void Bolid::shaderUse() {}
// check for potential camera movement user input
void Bolid::processKeyboardInput(GLFWwindow* window) {
	double curr_frame_time = glfwGetTime();
	delta_time = delta_time +(curr_frame_time - prev_frame_time);
	prev_frame_time = curr_frame_time;
	std::cout << delta_time << std::endl;
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
			speed += 0.5*log(SPEED_RATE);
			if (speed > MAX_SPEED)
				speed = MAX_SPEED;
		}
		else {
			speed -= 0.5*log(SPEED_RATE);
			if (speed < MAX_SPEED_REVERSE)
				speed = MAX_SPEED_REVERSE;
		}
			
	}
	else {
		if (speed > 0) {
			speed -= STOP_SPEED;
			if (speed < 0)
				speed = 0;
		}
		else {
			speed += STOP_SPEED;
			if (speed > 0)
				speed = 0;
		}
		
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (!inReverse) {
			speed -= SPEED_RATE;
			if (speed < 0)
				speed = 0;
		}
		else {
			speed += SPEED_RATE;
			if (speed > 0)
				speed = 0;
		}
		
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && speed!=0) {
		rotate(rotation_angle, glm::vec3(0.0, 1.0, 0.0));
		rotation_position += 1;
		if (rotation_position > 360)
			rotation_position = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && speed != 0) {
		rotate(rotation_angle, glm::vec3(0.0, -1.0, 0.0));
		rotation_position -= 1;
		if (rotation_position < -360)
			rotation_position = 0;
	}
	double x = sin(rotation_position*PI / 180) * speed;
	double z = cos(rotation_position*PI / 180)* speed;
	translate(glm::vec3(x, 0.0, z));
}
int Bolid::getRotationPosition() {
	return rotation_position;
}

