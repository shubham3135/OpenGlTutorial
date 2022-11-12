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

	Shader();
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void generate(const char* vertexShaderPath, const char* fragShaderPath);
	void activate();

	//utility func
	string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	//uniform functions
	void setMat4(const string& name, mat4 val);
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void set4Float(const std::string& name, float v1, float v2, float v3, float v4);
};
#endif