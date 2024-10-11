#include "Transform.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

const float Transform::toRadians = 3.14159265f / 180.0f;

Transform::Transform() : 
	model(glm::mat4(1.0f)), 
	position(glm::vec3(0.0f, 0.0f, 0.0f)), 
	rotation(glm::vec3(0.0f, 0.0f, 0.0f)), 
	scale(glm::vec3(1.0f, 1.0f, 1.0f)) {}

void Transform::UpdateModelMatrix(GLuint& uniformModel)
{
	//TRANSLATE then ROTATE then SCALE
	model = glm::mat4(1.0f);

	model = glm::translate(model, position);

	model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::scale(model, scale);

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
}