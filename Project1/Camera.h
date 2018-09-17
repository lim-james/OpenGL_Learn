#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::vec3 position, front, up, right, worldUp;

	GLfloat yaw, pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
public:
	Camera();
	Camera(glm::vec3, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat);

	void keyControl(bool*, GLfloat);
	void mouseControl(GLfloat, GLfloat);

	glm::mat4 calculateViewMatrix();

	~Camera();
};

