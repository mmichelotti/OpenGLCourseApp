#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
	
	void Render();
	void Clear();

	~Mesh();

private:
	GLuint VAO; //Vertex Array Object, it will hjold multiple VBO and other types of buffer
	GLuint VBO; //Vertex Buffer Object
	GLuint IBO; //Index Buffer Object
	GLsizei indexCount;

	void Create(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
};

