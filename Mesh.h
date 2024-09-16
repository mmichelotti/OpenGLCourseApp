#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	
	void Create(GLfloat *vertices, unsigned int *indices, unsigned int verticesAmount, unsigned int indicesAmount);
	void Render();
	void Clear();

	~Mesh();

private:
	GLuint VAO; //Vertex Array Object, it will hjold multiple VBO and other types of buffer
	GLuint VBO; //Vertex Buffer Object
	GLuint IBO; //Index Buffer Object
	GLsizei indexCount;
};

