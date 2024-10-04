#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Vec2.h"
#include "Time.h"

using namespace glm;

class Camera
{
public:
	Camera();
	Camera(vec3 initialPosition, Vec2<GLfloat> initialRotation);
	void KeyControl(bool* keys, float scrollOffset);
	void MouseControl(Vec2<GLfloat> deltaPos);
	
	vec3 GetCameraDirection(){ return normalize(front); }
	mat4 ViewMatrix();

	glm::vec3 GetCameraPosition() { return position; }
	~Camera();
	
private:
	vec3 position;

	vec3 up;
	vec3 right;
	vec3 front;

	Vec2<GLfloat> rotation;

	GLfloat moveSpeed = 5.0f;
	GLfloat turnSpeed = 0.5f;

	void Update();
};

