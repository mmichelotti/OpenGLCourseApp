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

class Model
{
public:
	Model();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void Clear();

	//TODO model matrix manipulation here
	void Translate(glm::vec3 offset);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(glm::vec3 scale);

	const glm::mat4 GetModelMatrix() const { return model; }
	~Model();

private:

	glm::mat4 model;
	std::vector<GLfloat> GetVertexBuffer(const aiMesh* mesh);
	std::vector<unsigned int> GetIndexBuffer(const aiMesh* mesh);
	void LoadMesh(const aiMesh *mesh);
	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadMaterials(const aiScene *scene);
	template<typename T>
	void Clear(std::vector<T*> collection);

	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;
	std::vector<unsigned int> meshToTex;
};

template<typename T>
inline void Model::Clear(std::vector<T*> collection)
{
	for (size_t i = 0; i < collection.size(); i++)
	{
		if (collection[i]) SAFE_DELETE(collection[i]);
	}
}
