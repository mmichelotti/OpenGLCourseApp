#pragma once
#include <vector>
#include <string>

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();
	void Load(const std::string& fileName);
	void Render();
	void Clear();
	~Model();

private:
	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);
	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;
	std::vector<unsigned int> meshToText;
};

