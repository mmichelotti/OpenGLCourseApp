#pragma once

#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void ClearModel();

	~Model();

private:
	std::vector<GLfloat> GetVertexBuffer(const aiMesh* mesh);
	std::vector<unsigned int> GetIndexBuffer(const aiMesh* mesh);
	void LoadMesh(const aiMesh *mesh);
	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadMaterials(const aiScene *scene);

	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;
	std::vector<unsigned int> meshToTex;
};

