#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// KB: TODO - header przechowuj�cy wszystkie u�ywane biblioteki?
// �eby ka�dy plik .h nie pod��cza� ich osobno

#include "include/utils.h"
#include "include/Model.h"
#include "include/camera.h"
#include "include/TylnySpoiler.h"
#include "include/PrzedniSpoiler.h"
#include "include/Kadlub.h"
#include "include/Bolid.h"
#include "include/Floor.h"

/*LightSource Test*/
#include "include/Light.h"
std::vector<GLfloat>vertices_ = {
	// positions          
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

	-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

	-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,

	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

	-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	/*	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f*/
};
std::vector<GLuint>indices_ = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
};


using namespace std;

const GLuint WIDTH = 1200, HEIGHT = 800;

Camera camera;

double mouse_prev_x;
double mouse_prev_y;
bool first_use = true;
float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f, 
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

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
unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		//unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}
		else
		{
			cout << "Cubemap tex failed to load at path: " << faces[i].c_str() << std::endl;
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
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
		ShaderProgram skyboxShader("skyboxShader.vert", "skyboxShader.frag");
		ShaderProgram BasicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag");

		// bolid
		Bolid bolid = Bolid(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,1.0,1.0), &BasicShader);
		bolid.translate(glm::vec3(0.0,-2.0,0.0));
		// floor
		Floor floor = Floor(&BasicShader);
		// skybox

		unsigned int skyboxVAO, skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		vector<std::string> faces
		{
			"../ResourceFiles/right.png",
			"../ResourceFiles/left.png",
			"../ResourceFiles/top.png",
			"../ResourceFiles/bottom.png",
			"../ResourceFiles/front.png",
			"../ResourceFiles/back.png"
		};
		unsigned int cubemapTexture = loadCubemap(faces);

		ShaderProgram LightShader("shaders/LightSourceShader.vert", "shaders/LightSourceShader.frag");
		/*Light source test*/
		//GLfloat ambient = 1.0;
		LightSource testLight(glm::vec3(1.0, 3.0, 1.0), glm::vec3(1.0, 1.0, 1.0), &LightShader);
		testLight.set_geometry(vertices_, indices_);
		testLight.set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
		testLight.bind_buffers();

		Object3D testOBJ = Object3D(glm::vec3(-2.0, 3.0, 1.0), glm::vec3(1.0, 1.0, 1.0), &BasicShader);
		testOBJ.set_geometry(vertices_, indices_);
		/*testOBJ.set_vertices(vertices_);
		testOBJ.set_indices(indices_);*/
		testOBJ.set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
		testOBJ.bind_buffers();

		// main event loop
		
		while (!glfwWindowShouldClose(window))
		{
			// check for camera movement
			camera.processKeyboardInput(window);

			// Clear color and depth buffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glm::mat4 projection = glm::perspective(glm::radians(camera.fov_), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

			static GLfloat rotAngle = 0.5f;

			// draw skybox as last
			glDepthMask(GL_FALSE);
			skyboxShader.Use();
			glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix())); // remove translation from the view matrix
			GLint projLoc = glGetUniformLocation(skyboxShader.get_programID(), "projection");
			GLint viewLoc = glGetUniformLocation(skyboxShader.get_programID(), "view");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			// skybox cube
			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);

			LightShader.Use();
			projLoc = glGetUniformLocation(LightShader.get_programID(), "projection");
			// setup view matrix - get it from camera object
			view = camera.getViewMatrix();
			viewLoc = glGetUniformLocation(LightShader.get_programID(), "view");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			testLight.draw();


			

			BasicShader.Use();
			projLoc = glGetUniformLocation(BasicShader.get_programID(), "projection");
			// setup view matrix - get it from camera object
			view = camera.getViewMatrix();
			viewLoc = glGetUniformLocation(BasicShader.get_programID(), "view");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "lightColor"), 1, glm::value_ptr(testLight.lightColor_));
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "lightPos"), 1, glm::value_ptr(testLight.centerPoint_));
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "viewPos"), 1, glm::value_ptr(camera.position_));

			bolid.draw();
			floor.draw();

			projLoc = glGetUniformLocation(BasicShader.get_programID(), "projection");
			// setup view matrix - get it from camera object
			view = camera.getViewMatrix();
			viewLoc = glGetUniformLocation(BasicShader.get_programID(), "view");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "lightColor"), 1, glm::value_ptr(testLight.lightColor_));
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "lightPos"), 1, glm::value_ptr(testLight.centerPoint_));
			testOBJ.rotate(rotAngle, glm::vec3(0.0, 0.0, 1.0));
			testOBJ.draw();

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
