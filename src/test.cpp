#pragma comment(lib, "winmm.lib")

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>

#include "include/utils.h"
#include "include/Model.h"
#include "include/camera.h"
#include "include/TylnySpoiler.h"
#include "include/PrzedniSpoiler.h"
#include "include/Kadlub.h"
#include "include/Bolid.h"
#include "include/Floor.h"
#include "include/Street.h"
#include "include/Cube.h"
#include "include/StreetLamps.h"

const unsigned int MAX_POINT_LIGHT_NR = 8;
std::vector<LightSource*> pointLights;

using namespace std;

const GLuint WIDTH = 1920, HEIGHT = 1080;

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

// keyboard interaction: close the program, brigthen lights, darken lights
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		for (const auto& p : pointLights) {
			p->diffuseStrength_ += 0.2;
			p->specularStrength_ += 0.2;
		}
	}
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		for (const auto& p : pointLights) {
			p->diffuseStrength_ -= 0.2;
			p->specularStrength_ -= 0.2;
		}
	}
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
		ShaderProgram LightShader("shaders/LightSourceShader.vert", "shaders/LightSourceShader.frag");
		ShaderProgram BasicShader("shaders/BasicShader.vert", "shaders/BasicShader.frag");

		// bolid
		Bolid bolid = Bolid(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,1.0,1.0), &BasicShader);
		bolid.translate(glm::vec3(0.0,-2.0,0.0));
		// floor
		Floor floor = Floor(&BasicShader);
		// road
		Street street = Street(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &BasicShader);
		// lamp post
		StreetLamps street_lamps = StreetLamps(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), &BasicShader, &LightShader, pointLights);

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

		/*Light source test*/
		DirectLight directLight(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, -1.0, -1.0), glm::vec3(1.0, 1.0, 1.0), 0.0, 0.1, 0.1);

		Object3D testOBJ = Object3D(glm::vec3(-2.0, 3.0, 1.0), glm::vec3(1.0, 1.0, 1.0), &BasicShader);
		testOBJ.set_geometry(CUBE_VERTICES, CUBE_INDICES);
		testOBJ.set_texture(LoadMipmapTexture(GL_TEXTURE0, "../ResourceFiles/carbon.png"));
		testOBJ.set_material();
		testOBJ.bind_buffers();

		// main event loop
		bool cameraInBolid = false;
		bool cameraThirdPerson = false;
		glm::vec2 lastVector = glm::vec2(0.0, -1.0);
		double prev_frame_time = glfwGetTime();
		double curr_frame_time;
		double delta_time = 0;
		const double PI = 3.14159265;

		//PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		while (!glfwWindowShouldClose(window))
		{
			// check for camera movement
			curr_frame_time = glfwGetTime();
			delta_time = delta_time + (curr_frame_time - prev_frame_time);
			prev_frame_time = curr_frame_time;
			if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && delta_time>0.1) {
				delta_time = 0;
				if (cameraInBolid) {
					camera.setIsInsideBolid(false);
					cameraInBolid = false;

				}
				else {
					camera.setIsInsideBolid(true);
					cameraInBolid = true;
				}
					
			}
			else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && delta_time > 0.1) {
				delta_time = 0;
				if (cameraInBolid && cameraThirdPerson) {
					cameraThirdPerson = false;
					camera.setIsThirdPersobView(false);
				}
				else if (cameraInBolid && !cameraThirdPerson) {
					cameraThirdPerson = true;
					camera.setIsThirdPersobView(true);
				}
			}
			if (cameraInBolid) {
				bolid.processKeyboardInput(window);
				if (cameraThirdPerson) {
					double x = 5.5 * cos((-bolid.getRotationPosition()-90)*PI / 180);
					double z = 5.5 * sin((-bolid.getRotationPosition()-90)*PI / 180);
					camera.setPosition(bolid.centerPoint_ + glm::vec3(x, 3.0, z));
					//std::cout << "Bolid Pos = " << bolid.centerPoint_.x << " " << bolid.centerPoint_.z << endl;
					//std::cout << "Rotation Pos = " << bolid.getRotationPosition() << " x = " << x << " z = " << z << endl;
				}
				else
					camera.setPosition(bolid.centerPoint_ + glm::vec3(0.0, 1.8, 0.0));
				camera.movementInBolid();
				camera.setRotationPosition(bolid.getRotationPosition());
			}
			else {
				
				camera.processKeyboardInput(window);
			}
			
			//cout << bolid.centerPoint_.x << " " << bolid.centerPoint_.y << " " << bolid.centerPoint_.z << endl; ;

			// Clear color and depth buffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glm::mat4 projection = glm::perspective(glm::radians(camera.fov_), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

			static GLfloat rotAngle = 0.5f;

			// draw skybox as last
			glDepthMask(GL_FALSE);
			skyboxShader.Use();
			glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix())); // remove translation from the view matrix
			pass_proj_view(projection, view, skyboxShader);
			// skybox cube
			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);

			view = camera.getViewMatrix();

			LightShader.Use();
			pass_proj_view(projection, view, LightShader);
			for (const auto& p : pointLights) {
				p->draw();
			}

			BasicShader.Use();
			glUniform1i(glGetUniformLocation(BasicShader.get_programID(), "lightCount"), pointLights.size());
			pass_proj_view(projection, view, BasicShader);
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "viewPos"), 1, glm::value_ptr(camera.position_));
			directLight.pass_parameters_to_shader(BasicShader);
			for (int i = 0; i < pointLights.size(); ++i) 
				pointLights[i]->pass_parameters_to_shader(BasicShader, i);
		
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "material.ambientColor"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "material.diffuseColor"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
			glUniform3fv(glGetUniformLocation(BasicShader.get_programID(), "material.specularColor"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
			glUniform1f(glGetUniformLocation(BasicShader.get_programID(), "material.shininess"), 32.0);

			bolid.draw();
			floor.draw();
			testOBJ.draw();
			street.draw(bolid.centerPoint_.z);

			street_lamps.draw();

			testOBJ.rotate(rotAngle, glm::vec3(0.0, 0.0, 1.0));

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
