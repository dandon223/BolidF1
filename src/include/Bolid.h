#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include <math.h> 

#include "include/shprogram.h"
#include "include/Model.h"
#include "PrzedniSpoiler.h"
#include "TylnySpoiler.h"
#include "Kadlub.h"
#include "Light.h"
#include "Kolo.h"

class Bolid : public Model {
private:
	double delta_time = 0.0f;
	double prev_frame_time = 0.0f;
	const float MOVEMENT_SPEED = 2.4f;
	double speed = 0.0f;
	double rotation_angle = 1.0f;
	int rotation_position = 0;
	const double MAX_SPEED = 0.5f;
	const double MAX_SPEED_REVERSE = -0.2f;
	bool inReverse = false;
	const double STOP_SPEED = 1.01f;
	const double SPEED_RATE = 1.01f;
	const double PI =3.14159265;

public:
	Bolid(const glm::vec3& centerPoint, const glm::vec3& scaleVector, ShaderProgram*);
	void setProjectionView(glm::mat4 p, glm::mat4 w);
	void shaderUse();
	void processKeyboardInput(GLFWwindow* window);
	int getRotationPosition();
};
