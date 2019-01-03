#include <iostream>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "window.h"

bool glCalls();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool setWindow(GLFWwindow* w);
void vSync(float& dt, float& lastTime);

int main()
{
	if (!glCalls())return 0;
	int WIDTH = 1200, HEIGHT = 900;

	// Open a window and create its OpenGL context
	Window w(WIDTH, HEIGHT, "Procedurellt");
	GLFWwindow* window = w.getWindow();
	if (!setWindow(window))return 0;
	float dT = 0.0f, lastTime = 0.0f;
	int display_w, display_h;


	while (!glfwWindowShouldClose(window))
	{
		vSync(dT, lastTime);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		// Swap the screen buffers and make glcalls
		glfwSwapBuffers(window);
		if (!glCalls())return 0;

	}
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
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDisable(GL_TEXTURE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	glfwSetKeyCallback(w, key_callback);
	return true;
}