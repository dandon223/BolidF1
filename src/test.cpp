#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// KB: TODO - header przechowuj¹cy wszystkie u¿ywane biblioteki?
// ¿eby ka¿dy plik .h nie pod³¹cza³ ich osobno

#include "include/utils.h"
#include "include/Model.h"
#include "include/camera.h"
#include "TylnySpoiler.h"
#include "PrzedniSpoiler.h"
#include "Kadlub.h"
#include "Bolid.h"


using namespace std;

const GLuint WIDTH = 1200, HEIGHT = 800;

Camera camera;

double mouse_prev_x;
double mouse_prev_y;
bool first_use = true;

	// keyboard interaction: close the program
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

	// mouse movement interaction: rotate camera according to user's input
void mouseCallback(GLFWwindow* window, double x_pos, double y_pos) {
	double x_offset, y_offset;
	if (first_use == true) {
		x_offset = y_offset = 0.0f;
		first_use = false;
	}
	else {
		x_offset = x_pos - mouse_prev_x;
		y_offset = mouse_prev_y - y_pos;
	}
	mouse_prev_x = x_pos;
	mouse_prev_y = y_pos;
	camera.processMouseMovement(x_offset, y_offset);
}

	// mouse scroll interaction: change FOV, effectively - zoom in/out
void scrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
	camera.processMouseScroll(y_offset);
}

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Samochodzik robi wrum", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);

		// user interaction setup
		glfwSetKeyCallback(window, keyCallback);			// keyboard
		glfwSetCursorPosCallback(window, mouseCallback);	// mouse movement
		glfwSetScrollCallback(window, scrollCallback);		// mouse scroll

		// capture and hide mouse cursor 
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		glEnable(GL_DEPTH_TEST);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		// Build, compile and link shader program
		ShaderProgram CubeShader("shaders/CubeShader.vert", "shaders/CubeShader.frag");
		// bolid
		Bolid bolid = Bolid();
		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// check for camera movement
			camera.processKeyboardInput(window);

			// Clear color and depth buffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glm::mat4 projection = glm::perspective(glm::radians(camera.fov_), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			GLint projLoc = glGetUniformLocation(CubeShader.get_programID(), "projection");
			// setup view matrix - get it from camera object
			glm::mat4 view = camera.getViewMatrix();
			GLint viewLoc = glGetUniformLocation(CubeShader.get_programID(), "view");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			
			
			static GLfloat rotAngle = 0.3f;


			bolid.shaderUse();
			bolid.setProjectionView(projection, view);
			//bolid.rotate(rotAngle, glm::vec3(0.0, 1.0, 0.0),glm::vec3(0.0,0.0,0.0));
			bolid.draw();

			

			// Swap the screen buffers
			glfwSwapBuffers(window);

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}