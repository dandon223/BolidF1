#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/utils.h"
#include "include/Object3D.h"

// KB: TODO - header przechowuj¹cy wszystkie u¿ywane biblioteki?
// ¿eby ka¿dy plik .h nie pod³¹cza³ ich osobno

#include "include/shprogram.h"
#include "include/camera.h"

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
		//ShaderProgram shader_program("gl_05.vert", "gl_05.frag");
		ShaderProgram CubeShader("shaders/CubeShader.vert", "shaders/CubeShader.frag");

		/*Cube* box1 = new Cube(&CubeShader);
		Cube* box2 = new Cube(&CubeShader);
		
		box1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.bmp"));
		box2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.bmp"));

		box2->translate(glm::vec3(0.0f, 2.0f, 0.0f));
		box1->scale(glm::vec3(1.0f, 1.0f, 1.0f));
		box2->scale(glm::vec3(1.0f, 1.0f, 1.0f));*/


		/*BIG TEST*/
		std::vector<GLfloat> vertices = {
		0.0f, -0.6f, 0.0f,		0.5f,  0.0f,// 0
		0.3f, -0.2f, 0.0f,		1.0f,  0.2f,// 1
		-0.3f, -0.2f, 0.0f,		0.03f,  0.2f,// 2
		0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3
		-0.3f, 0.6f, 0.0f,		0.03f,  1.0f,// 4
		};
		std::vector<GLuint> indices = {
			0, 1, 2,
			1, 3, 2,
			2, 3, 4,
		};
		std::vector<GLfloat> vertices1 = {
			 0.0f, -0.6f, 0.0f,		0.5f,  0.0f,// 0
			 0.3f, -0.2f, 0.0f,		1.0f,  0.2f,// 1
			 -0.3f, -0.2f, 0.0f,	0.0f,  0.2f,// 2
			0.3f, 0.6f, 0.0f,		1.0f,  1.0f,// 3
			-0.3f, 0.6f, 0.0f,		0.0f,  1.0f,// 4

			0.0f, -0.6f, 0.01f,		0.5f,  0.0f,// 5
			0.3f, -0.2f, 0.01f,		1.0f,  0.2f,// 6
			-0.3f, -0.2f, 0.01f,	0.0f,  0.2f,// 7
			0.3f, 0.6f, 0.01f,		1.0f,  1.0f,// 8
			-0.3f, 0.6f, 0.01f,		0.0f,  1.0f,// 9
		};
		std::vector<GLuint> indices1 = {
			0,5,1,
			5,6,1,
			0,5,2,
			2,5,7,
			1,6,3,
			6,8,3,
			2,7,4,
			7,9,4,
			3,8,4,
			8,9,4,
			6,8,7,
			8,9,7,
			5,6,7,
		};
		std::vector<GLfloat> vertices2 = {
			0.5f, 0.1f, 0.0f,		1.0f,1.0f,	//0
			-0.98f, 0.1f , 0.0f,	0.0f,1.0f,	//1
			-0.98f,0.0f, -0.4f,		1.0f, 0.0f, //2
			0.5f,0.0f, -0.4f,		0.0f,0.0f,	//3
			0.5f, 0.15f, -0.3f,		0.0f,1.0f,	//4
			-0.98f, 0.15f, -0.3f,	0.0f,0.0f,	//5

		};
		std::vector<GLuint> indices2 = {
			0,3,4,
			1,2,5,
			0,3,1,
			3,2,1,
			1,0,4,
			1,4,5,
			2,3,4,
			2,4,5,
		};
		std::vector<GLfloat> vertices3 = {
			0.0f, -0.5f, 0.0f,		0.0f,0.0f,	//0
			0.02f, -0.5f , 0.0f,	0.0f, 1.0f, //1
			0.02f, -0.5f , -0.02f,  1.0f, 1.0f, //2
			0.0f, -0.5f, -0.02f,	1.0f, 0.0f, //3
			0.2f,0.5f, 0.0f,		1.0f, 0.0f,	//4
			0.24f,0.5f, 0.0f,		0.0f, 0.0f, //5
			0.24f, 0.5f, -0.02f,	0.0f,1.0f,	//6
			0.2f, 0.5f, -0.02f,		1.0f, 1.0f,	//7

		};
		std::vector<GLuint> indices3 = {
			0,1,2,
			0,2,3,
			1,2,6,
			1,6,5,
			0,1,5,
			0,5,4,
			3,0,4,
			3,4,7,
			3,2,6,
			3,6,7,
			4,5,6,
			4,6,7,
		};
		Object3D* part1 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -0.75), glm::vec3(1.0, 1.0, 1.0), &CubeShader);
		Object3D* part2 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.5), glm::vec3(1.0, 1.0, 1.0), &CubeShader);
		Object3D* part3 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(-0.2, 0.1, -0.51), glm::vec3(1.0, 1.0, 1.0), &CubeShader);
		Object3D* part4 = new Object3D(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.05, -0.62, -0.04), glm::vec3(1.0, 1.0, 1.0), &CubeShader);
		part1->set_geometry(vertices, indices);
		//part2->set_geometry(vertices1, indices1);
		//part3->set_geometry(vertices2, indices2);
		//part4->set_geometry(vertices3, indices3);
		//part1->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
		//part2->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
		//part3->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));
		//part4->set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/spoiler.png"));

		Model testModel(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0));
		/*testModel.add(box1);
		testModel.add(box2);*/
		testModel.add(part1);
		testModel.add(part2);
		testModel.add(part3);
		testModel.add(part4);
		testModel.bind_buffers();
		int i = 0;

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// check for camera movement
			camera.processKeyboardInput(window);

			// Clear color and depth buffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// setup projection matrix
			glm::mat4 projection = glm::perspective(glm::radians(camera.fov_), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			GLint projLoc = glGetUniformLocation(CubeShader.get_programID(), "projection");
			// setup view matrix - get it from camera object
			glm::mat4 view = camera.getViewMatrix();
			GLint viewLoc = glGetUniformLocation(CubeShader.get_programID(), "view");
			//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(box1.model_));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			// Bind Textures using texture units
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, texture1);
			//glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture1"), 1);

			static GLfloat rotAngle = 0.3f;
			static glm::vec3 transVector(0.1f, 0.0f, 0.0f);
			
			//testModel.translate(glm::vec3(0.0, 0.0, 0.0005));
			//testModel.rotate(rotAngle, glm::vec3(0.0, 0.0, 1.0), glm::vec3(3.0, 0.0, 0.0));

			//shader_program.Use();
			CubeShader.Use();

			testModel.draw();

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