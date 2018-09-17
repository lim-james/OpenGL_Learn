#include "Shader.h"

void Shader::addShader(GLuint program, const char* code, GLenum type) {
	GLuint shader = glCreateShader(type);

	const GLchar* glCode[1];
	glCode[0] = code;

	GLint len[1];
	len[0] = strlen(code);

	glShaderSource(shader, 1, glCode, len);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("SHADER COMPILATION FAILED: %s", eLog);
		return;
	}

	glAttachShader(program, shader);
}

void Shader::compileShaders(const char* vertexCode, const char* fragmentCode) {
	ID = glCreateProgram();

	if (!ID) {
		printf("PROGRAM CREATION FAILED");
		return;
	}

	addShader(ID, vertexCode, GL_VERTEX_SHADER);
	addShader(ID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
		printf("PROGRAM LINKAGE FAILED: %s", eLog);
		return;
	}

	glValidateProgram(ID);
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
		printf("PROGRAM VALIDATION FAILED: %s", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(ID, "projection");
	uniformModel = glGetUniformLocation(ID, "model");
	uniformView = glGetUniformLocation(ID, "view");
}

std::string Shader::fileContents(const char* file) {
	std::string content;
	std::ifstream ifs(file, std::ios::in);

	if (!ifs.is_open()) {
		printf("FAILED TO READ FILE: %s\n", file);
		return "";
	}

	std::string line;
	
	while (std::getline(ifs, line)) {
		content.append(line + "\n");
	}

	return content;
}


Shader::Shader() : ID(0), uniformModel(0), uniformProjection(0) {
}

//void Shader::create(const char* vertexCode, const char* fragmentCode) {
//	compileShaders(vertexCode, fragmentCode);
//}

void Shader::create(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = fileContents(vertexFile);
	std::string fragmentCode = fileContents(fragmentFile);
	compileShaders(vertexCode.c_str(), fragmentCode.c_str());
}

GLuint Shader::getProjectionLocation() {
	return uniformProjection;
}

GLuint Shader::getModelLocation() {
	return uniformModel;
}

GLuint Shader::getViewLocation() {
	return uniformView;
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::clear() {
	if (ID) {
		glDeleteProgram(ID);
		ID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
}

Shader::~Shader()
{
	clear();
}
