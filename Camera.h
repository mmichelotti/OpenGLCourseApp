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
	Camera(vec3 initialPosition, vec3 initialWorldUp, Vec2<GLfloat> initialRotation, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed);
	void KeyControl(bool* keys);
	void MouseControl(Vec2<GLfloat> deltaPos);
	mat4 ViewMatrix();
	~Camera();
private:
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;

	Vec2<GLfloat> rotation;



	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void Update();
};

