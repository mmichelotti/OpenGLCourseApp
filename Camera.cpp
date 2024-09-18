#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(vec3 initialPosition, vec3 initialWorldUp, Vec2<GLfloat> initialRotation, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed)
{
	position = initialPosition;
	worldUp = initialWorldUp;
	rotation = initialRotation;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = initialMoveSpeed;
	turnSpeed = initialTurnSpeed;

	Update();
}

void Camera::KeyControl(bool* keys)
{
	GLfloat velocity = moveSpeed * Time::GetDeltaTime();

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::MouseControl(Vec2<GLfloat> deltaPos)
{
	deltaPos *= turnSpeed;

	rotation.x += deltaPos.x;
	rotation.y += deltaPos.y;

	if (rotation.y > 89.0f)
	{
		rotation.y = 89.0f;
	}

	if (rotation.y < -89.0f)
	{
		rotation.y = -89.0f;
	}

	Update();
}

mat4 Camera::ViewMatrix()
{
	return lookAt(position, position + front, up);
}



void Camera::Update()
{
	front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	front.y = sin(glm::radians(rotation.y));
	front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}