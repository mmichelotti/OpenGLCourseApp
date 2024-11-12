#pragma once
#include <GL/glew.h>
#include <vector>
#include "GLM/glm.hpp"
enum Primitive
{
	PLANE,
	CUBE,
	SPHERE,
	PYRAMID
};
class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
	Mesh(Primitive mesh);
	void AverageNormals(unsigned int vLength, unsigned int normalOffset);
	
	void Render();
	void Clear();

	~Mesh();

private:
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	GLuint VAO; //Vertex Array Object, it will hjold multiple VBO and other types of buffer
	GLuint VBO; //Vertex Buffer Object
	GLuint IBO; //Index Buffer Object
	GLsizei indexCount;
	void Create();
};

