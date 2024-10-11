#include "Model.h"
#include "Global.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

Model::Model()
{
	model = glm::mat4(1.0f);
}

void Model::RenderModel()
{
	if (!meshes[0]) return;
	for (size_t i = 0; i < meshes.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textures.size() && textures[materialIndex])
		{
			textures[materialIndex]->Use();
		}

		meshes[i]->Render();
	}
}

void Model::LoadModel(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);
}

void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]]);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

std::vector<GLfloat> Model::GetVertexBuffer(const aiMesh* mesh)
{
	std::vector<GLfloat> vertices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D& vertex = mesh->mVertices[i];
		aiVector3D* texture = mesh->mTextureCoords[0];
		aiVector3D& normals = mesh->mNormals[i];
		Vec2<GLfloat> uv = texture ? Vec2<GLfloat>(texture[i].x, texture[i].y) : Vec2<GLfloat>();

		//x,y,z then u,v then r,g,b 
		vertices.insert(vertices.end(), { vertex.x, vertex.y, vertex.z });
		vertices.insert(vertices.end(), { uv.x, uv.y });
		vertices.insert(vertices.end(), { -normals.x, -normals.y, -normals.z });
	}
	return vertices;
}

std::vector<unsigned int> Model::GetIndexBuffer(const aiMesh* mesh)
{
	std::vector<unsigned int> indices;
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	return indices;
}

void Model::LoadMesh(const aiMesh* mesh)
{
	Mesh* newMesh = new Mesh(GetVertexBuffer(mesh), GetIndexBuffer(mesh));
	meshes.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene* scene)
{
	textures.resize(scene->mNumMaterials);
	
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textures[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				textures[i] = new Texture(texPath.c_str());

				if (!textures[i]->LoadRGB())
				{
					printf("Failed to load texture at: %s\n", texPath);
					SAFE_DELETE(textures[i]);
				}
			}
		}

		if (!textures[i])
		{
			textures[i] = new Texture("Textures/plain.png");
			textures[i]->LoadRGBA();
		}
	}
}

void Model::Clear()
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		if (meshes[i]) SAFE_DELETE(meshes[i]);
	}

	for (size_t i = 0; i < textures.size(); i++)
	{
		if (textures[i]) SAFE_DELETE(textures[i]);
	}
}

void Model::Translate(glm::vec3 offset) 
{
	model = glm::translate(model, offset);
}

void Model::Rotate(float angle, glm::vec3 axis) 
{
	model = glm::rotate(model, angle, axis);
}

void Model::Scale(glm::vec3 scale) 
{
	model = glm::scale(model, scale); 
}

Model::~Model()
{
	Clear();
}
