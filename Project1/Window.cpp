#include "Window.h"

void Window::createCallbacks() {
	glfwSetKeyCallback(main, handleKeys);
	glfwSetCursorPosCallback(main, handleMouse);
}

void Window::handleKeys(GLFWwindow* w, int key, int code, int action, int mode) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(w, GL_TRUE);
	}

	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			window->keys[key] = true;
			printf("PRESSED %d\n", key);
		} else if (action == GLFW_RELEASE) {
			window->keys[key] = false;
			printf("RELEASED %d\n", key);
		}
	}
}

void Window::handleMouse(GLFWwindow* w, double xPos, double yPos) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));

	if (window->mouseFirstMoved) {
		window->lastX = xPos;
		window->lastY = yPos;
		window->mouseFirstMoved = false;
	}

	window->xChange = xPos - window->lastX;
	window->yChange = window->lastY - yPos;

	window->lastX = xPos;
	window->lastY = yPos;
}


Window::Window() : width(600), height(800) {
	for (size_t i = 0; i < 1024; ++i) {
		keys[i] = false;
	}
}

Window::Window(GLint w, GLint h) : width(w), height(h) {
	for (size_t i = 0; i < 1024; ++i) {
		keys[i] = false;
	}
}

int Window::initialise() {
	if (!glfwInit()) {
		printf("GLFW INIT FAILED");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	main = glfwCreateWindow(width, height, "Window", NULL, NULL);

	if (!main) {
		printf("WINDOW CREATION FAILED");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(main, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(main);

	createCallbacks();
	glfwSetInputMode(main, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		printf("GLEW INIT FAILED");
		glfwDestroyWindow(main);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(main, this);

	return 0;
}

GLint Window::getBufferWidth() {
	return bufferWidth;
}
GLint Window::getBufferHeight() {
	return bufferHeight;
}

bool Window::getShouldClose() {
	return glfwWindowShouldClose(main);
}

GLfloat Window::getXChange() {
	GLfloat change = xChange;
	xChange = 0.0f;
	return change;
}

GLfloat Window::getYChange() {
	GLfloat change = yChange;
	yChange = 0.0f;
	return change;
}

void Window::swapBuffers() {
	glfwSwapBuffers(main);
}

Window::~Window() {
	glfwDestroyWindow(main);
	glfwTerminate();

}
