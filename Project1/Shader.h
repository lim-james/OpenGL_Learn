#pragma once

#include <stdio.h>
#include <string>
#include <fstream>

#include <GL/glew.h>

class Shader {
private:
	GLuint ID, uniformProjection, uniformModel, uniformView;

	void addShader(GLuint, const char*, GLenum);
	void compileShaders(const char*, const char*);

	std::string fileContents(const char*);
public:
	Shader();
	
	void create(const char*, const char*);
	
	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();

	void use();
	void clear();

	~Shader();
};

