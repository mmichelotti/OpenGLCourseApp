#include "Mesh.h"
#include <vector>

/// <summary>
/// Constructor for class Mesh
/// </summary>
Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
	Create(vertices, indices);
}


//Accessing the arrays by reference
/*
	This means that if vertices or indices changes here, they will change even the original passed by arguments
	Literally like c# ref argument
	But in this case, adding the keyword const promises that the value of vertices and indices won't change
	So this all mean that we are READING ONLY a direct reference to an array
*/
void Mesh::Create(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
{
	unsigned int verticesAmount = vertices.size();
	unsigned int indicesAmount = indices.size();
	indexCount = indicesAmount;

	//generate VAO VBO IBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Bind VAO VBO IBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesAmount, indices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesAmount, vertices.data(), GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);//every 5 elements of the array there is a vertex
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	/*
	    EXPLANATION
		0 / 1 / 2 etc are the layout defined within the vertex shader
		Argument 1 : Attribute type
			0 = Actual Position
			1 = Texture Coordinate (UV)
			2 = Normal 
		Argument 2 : Length of the array for that attribute
		Argument 5 : (How many elements in the array in between the each vertex) * size (5 in this case)
		Argument 6 : How much offset from the starting position of the array
	*/



	//Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Render()
{
	//Bind VAO IBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	//Unbind VAO IBO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Clear()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	indexCount = 0;
}

Mesh::~Mesh()
{
	Clear();
}