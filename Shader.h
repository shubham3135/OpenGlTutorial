#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Shader {
public:
	unsigned int id;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void activate();

	//utility func
	string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	//uniform functions
	void setMat4(const string& name, mat4 val);
};
#endif