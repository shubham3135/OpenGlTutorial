#include "Shader.h"

Shader::Shader() {}

Shader::Shader(const char* vertexShaderPath, const char* fragShaderPath) {
	generate(vertexShaderPath, fragShaderPath);
}


void Shader::generate(const char* vertexShaderPath, const char* fragmentShaderPath) {
	int success;
	char infoLog[512];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		cout << "Error with frag shader comp. : " << endl << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::activate() {
	glUseProgram(id);
}

string Shader::loadShaderSrc(const char* fileName) {
	ifstream file;
	stringstream buf;
	string ret = "";

	file.open(fileName);
	if (file.is_open()) {
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		cout << "Could not open " << fileName << endl;
	}
	file.close();
	return ret;
}

GLuint Shader::compileShader(const char* filepath, GLenum type) {
	int success;
	char infoLog[512];

	GLuint ret = glCreateShader(type);
	string shaderSrc = loadShaderSrc(filepath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(ret, 1, &shader, NULL);
	glCompileShader(ret);

	glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ret, 512, NULL, infoLog);
		cout << "Error with frag shader comp. : " << endl << infoLog << endl;
	}
	return ret;
}

void Shader::setMat4(const string& name, mat4 val) {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(val));
}


void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}
