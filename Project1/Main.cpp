#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Window.h"
#include "Camera.h"

const GLuint WIDTH = 1600, HEIGHT = 900;
const float rad = 3.14159265f / 180.0f;

Window *mainWindow;
std::vector<Shader*> shaders;
std::vector<Mesh*> objects;
Camera camera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";

void createObjects() {
	unsigned int indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};

	GLfloat vertices[] = {
		// front
		-1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,
		 1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,
		 1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
	};

	for (int i = 0; i < 2; ++i)
	{
		Mesh *obj = new Mesh();
		obj->create(24, vertices, 36, indices);
		objects.push_back(obj);
	}
}

void createShaders() {
	Shader *shader = new Shader();
	shader->create(vShader, fShader);
	shaders.push_back(shader);
}

int main() {
	mainWindow = new Window(800, 600);
	mainWindow->initialise();

	createObjects();
	createShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);

	GLuint uniformModel, uniformProjection, uniformView;

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow->getBufferWidth() / (GLfloat)mainWindow->getBufferHeight(), 0.1f, 100.f);

	while (!mainWindow->getShouldClose()) {
		GLfloat now = glfwGetTime(); 
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();

		camera.keyControl(mainWindow->getKeys(), deltaTime);
		camera.mouseControl(mainWindow->getXChange(), mainWindow->getYChange());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int s = 0; s < shaders.size(); ++s) {
			Shader *shader = shaders[s];

			shader->use();
			uniformModel = shader->getModelLocation();
			uniformProjection = shader->getProjectionLocation();
			uniformView = shader->getViewLocation();

			for (int i = 0; i < objects.size(); ++i) {
				glm::mat4 model;
				model = glm::translate(model, glm::vec3(0.0f, i * 2.0f, -10.0f));

				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
				glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

				objects[i]->render();
			}

			glUseProgram(0);
		}
		
		mainWindow->swapBuffers();
	}

	return 0;
}