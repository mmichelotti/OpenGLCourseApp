#include "Model.h"

Model::Model()
{
}

void Model::Load(const std::string& fileName)
{
	Assimp::Importer importer;
	unsigned int config = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices;
	const aiScene* scene = importer.ReadFile(fileName, config);
	if (!scene)
	{
		printf("Model %s failed to load", importer.GetErrorString());
		return;
	}
	LoadNode(scene->mRootNode, scene);
	LoadMaterials(scene);
}

void Model::Render()
{
}

void Model::Clear()
{
}

Model::~Model()
{
}

void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		//LoadMesh(scene->mMeshes[node->mMeshes[i], scene);
	}
}


void Model::LoadMaterials(const aiScene* scene)
{
}



