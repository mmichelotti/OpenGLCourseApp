#include "Camera.h"
#include "World.h"
#include <unordered_map>
#include <functional>

using namespace std;

Camera::Camera()
{
}

Camera::Camera(vec3 initialPosition, Vec2<GLfloat> initialRotation, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed)
{
	position = initialPosition;
	rotation = initialRotation;
	moveSpeed = initialMoveSpeed;
	turnSpeed = initialTurnSpeed;

	Update();
}

void Camera::KeyControl(bool* keys)
{
	const unordered_map<int, vec3> movementMap = 
	{
		{ GLFW_KEY_W, + front },
		{ GLFW_KEY_S, - front },
		{ GLFW_KEY_D, + right },
		{ GLFW_KEY_A, - right },
		{ GLFW_KEY_E, + up	  },
		{ GLFW_KEY_Q, - up	  } 
	};

	const float deltaVelocity = moveSpeed * Time::Delta;

	for (const auto& [key, direction] : movementMap)
	{
		if (keys[key]) position += direction * deltaVelocity;
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

	right = glm::normalize(glm::cross(front, World::Up));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}