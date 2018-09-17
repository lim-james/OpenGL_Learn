#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow * main;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange; 
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow*, int, int, int, int);
	static void handleMouse(GLFWwindow*, double, double);

public:
	Window();
	Window(GLint, GLint);

	int initialise();

	GLint getBufferWidth();
	GLint getBufferHeight();

	bool getShouldClose();

	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers();

	~Window();
};

