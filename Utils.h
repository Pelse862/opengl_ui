#pragma once
#include "glm\glm.hpp"
#include <vector>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <glm/gtc/matrix_transform.hpp>



namespace util{
	bool loadOBJ(const char * path,
		::std::vector < glm::vec3 > & out_vertices,
		::std::vector < glm::vec2 > & out_uvs,
		::std::vector < glm::vec3 > & out_normals);

	GLuint bindLoadedObj(const ::std::vector < glm::vec3 >& obj_vertices,
						 const ::std::vector < glm::vec2 >& obj_uvs,
						 const ::std::vector < glm::vec3 >& obj_normals);
	void computeMatricesFromInputs(GLFWwindow* window);

	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
}