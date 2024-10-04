#include "Camera.h"
#include "World.h"

Camera::Camera() : position(vec3(0.0f, 0.0f, 0.0f)), rotation(Vec2<GLfloat>(0.0f, 0.0f))
{
	Update();
}

Camera::Camera(vec3 initialPosition, Vec2<GLfloat> initialRotation) : position(initialPosition), rotation(initialRotation)
{
	Update();
}

void Camera::KeyControl(bool* keys, float scrollDelta)
{
	vec3 direction = vec3(0.0f, 0.0f, 0.0f);

	if (keys[GLFW_KEY_W]) direction += front;
	if (keys[GLFW_KEY_S]) direction -= front;
	if (keys[GLFW_KEY_D]) direction += right;
	if (keys[GLFW_KEY_A]) direction -= right;
	if (keys[GLFW_KEY_E]) direction += up;
	if (keys[GLFW_KEY_Q]) direction -= up;

	if (length(direction) > 0) direction = normalize(direction);

	moveSpeed += scrollDelta;
	moveSpeed = glm::max(0.1f, moveSpeed);
	const float deltaVelocity = moveSpeed * Time::Delta;

	position += direction * deltaVelocity;
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