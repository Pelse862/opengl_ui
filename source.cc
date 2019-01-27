#pragma once
#include "Utils.h"
#include <iostream>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "window.h"
#include "createShader.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Button.h"
#include <memory>

const int WIDTH = 1200, HEIGHT = 900;


bool glCalls();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int button, int action, int modifier);
bool setWindow(GLFWwindow* w);
void vSync(float& dt, float& lastTime);
void setNewClearColor();

//Create a simple button, 
//TODO create "ui handler"
//TODO bind to a new quad and create shaders
Button testButton(0.45, 0.55, 0.45, 0.55, setNewClearColor);


int main()
{
	if (!glCalls())return 0;

	// Open a window and create its OpenGL context
	Window w(WIDTH, HEIGHT, "UI");
	GLFWwindow* window = w.getWindow();
	if (!setWindow(window))return 0;
	float dT = 0.0f, lastTime = 0.0f;
	int display_w, display_h;

	//create shaders
	std::string vertPath = "D:/Program Files (x86)/Visual code/opengl_ui/BasicVert.glsl";
	std::string fragPath = "D:/Program Files (x86)/Visual code/opengl_ui/BasicFrag.glsl";
	createShader basicShader;
	basicShader.creteFragmentShader(fragPath.c_str());
	basicShader.creteVertexShader(vertPath.c_str());
	basicShader.detatch();
	

	GLuint MatrixID = glGetUniformLocation(basicShader.getProgramId(), "MVP");
	
	//load an obj file
	char* path = "D:/Program Files (x86)/Visual code/opengl_ui/obj.obj";
	::std::vector < glm::vec3 > obj_vertices;
	::std::vector < glm::vec2 > obj_uvs;
	::std::vector < glm::vec3 > obj_normals;
	util::loadOBJ(path, obj_vertices, obj_uvs, obj_normals);
	GLuint vao = util::bindLoadedObj(obj_vertices, obj_uvs, obj_normals);
	

	glfwPollEvents();
	glBindVertexArray(vao);
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window))
	{
		vSync(dT, lastTime);
		
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.use();
		util::computeMatricesFromInputs(window);
		glm::mat4 ProjectionMatrix = util::getProjectionMatrix();
		glm::mat4 ViewMatrix = util::getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		
		glDrawArrays(GL_TRIANGLES, 0, obj_vertices.size());

		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		glfwSwapBuffers(window);
		if (!glCalls())return 0;
		glfwPollEvents();
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glfwTerminate();


	return 0;
}

void vSync(float& dT, float& lastTime)
{
	if (dT > 1.f / 30.f) {
		lastTime = glfwGetTime();
	}
	else {
		dT = glfwGetTime() - lastTime;
		vSync(dT, lastTime);
	}
	//printf("%f ms/frame\n", dT);
}

//glfw calls
bool glCalls()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_ALPHA_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool setWindow(GLFWwindow* w)
{

	glfwMakeContextCurrent(w); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	glfwSetInputMode(w, GLFW_STICKY_KEYS, GL_TRUE);
	//set mouse callback
	glfwSetKeyCallback(w, key_callback);
	//Set mouse callback
	glfwSetMouseButtonCallback(w, mouse_callback);
	return true;
}

void setNewClearColor() {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
}

// Is called whenever a mouse button is pressed/released via GLFW
void mouse_callback(GLFWwindow* window, int button, int action, int modifier)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1) {
		testButton.checkClick(xpos/double(WIDTH), ypos/double(HEIGHT) );
	}
}