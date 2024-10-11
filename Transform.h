#pragma once
#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <GLM/glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Global.h"

class Transform
{
public:
	Transform();
	void SetPosition(const glm::vec3& position) { this->position = position; }
	void SetRotation(const glm::vec3& rotation) { this->rotation = rotation * toRadians; }
	void SetScale(const glm::vec3& scale) { this->scale = scale; }
	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetRotation() { return rotation / toRadians; }
	glm::vec3 GetScale() { return scale; }
	void UpdateModelMatrix(GLuint& uniformModel);

private:
	static const float toRadians;
	glm::mat4 model;
	glm::vec3 position, rotation, scale;

};

