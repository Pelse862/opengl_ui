#pragma once
#include <string>
#include "GLFW\glfw3.h"
#include <iostream>

class Window
{
public:
	Window(int w, int h, std::string n) : width(w), height(h), name(n){}
	GLFWwindow* getWindow(){
		
		w = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
		if (w == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return nullptr;
		}
		return w;
	}
	bool isWindowSet(GLFWwindow* window) {
		if (window)
		{
			std::cout << "Window is not set Properly" << std::endl;
			glfwTerminate();
			return false;
		}
		return true;
	}

	~Window() = default;

private:
	GLFWwindow* w;
	int width;
	int height;
	std::string name;
	
};