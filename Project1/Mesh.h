#pragma once

#include <GL/glew.h>

class Mesh {
private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

public:
	Mesh();

	void create(unsigned int, GLfloat*, unsigned int, unsigned int*);
	void render();
	void clear();

	~Mesh();
};

