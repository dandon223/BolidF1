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

#include "shprogram.h"
#include "camera.h"

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

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

// KB: potrzebujemy tego?
ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
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
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);
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

		// Build, compile and link shader program
		ShaderProgram shader_program("gl_05.vert", "gl_05.frag");

		// Set up vertex data 
		GLfloat vertices[] = {
			// coordinates			// color			// texture
			0.5f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//0
			-0.5f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//1
			-0.5f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//2
			0.5f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//3

			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//4
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//5
			0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//6
			0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//7

			-0.5f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//8
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//9
			0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//10
			0.5f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//11

			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//12
			-0.5f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//13
			0.5f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//14
			0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//15

			-0.5f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//16
			-0.5f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//17
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//18
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f,  1.0f,	//19

			0.5f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//20
			0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//21
			0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//22
			0.5f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f		//23
		};


		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			18, 17, 19,
			20, 21, 22,
			20, 22, 23
		};

		GLuint VBO, EBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// vertex texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

							  // Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/bricks.bmp");

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// check for camera movement
			camera.processKeyboardInput(window);

			// Clear color and depth buffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Bind Textures using texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(shader_program.get_programID(), "Texture0"), 0);

			// use shader
			shader_program.Use();

			// setup transformation matrix
			glm::mat4 trans = glm::mat4(1.0f);
			static GLfloat rot_angle = 0.0f;
			trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, -5.0f));
			trans = glm::rotate(trans, -glm::radians(rot_angle), glm::vec3(0.5, 1.0, 0.0));
			rot_angle = fmod((rot_angle + 0.4f), 360.0f);
			GLuint transformLoc = glGetUniformLocation(shader_program.get_programID(), "transform");
				
			// setup projection matrix
			glm::mat4 projection = glm::perspective(glm::radians(camera.fov_), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			GLint projLoc = glGetUniformLocation(shader_program.get_programID(), "projection");

			// setup view matrix - get it from camera object
			glm::mat4 view = camera.getViewMatrix();
			GLint viewLoc = glGetUniformLocation(shader_program.get_programID(), "view");

			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);	

			// Swap the screen buffers
			glfwSwapBuffers(window);

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}