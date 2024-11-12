#include "Mesh.h"
#include <vector>

/// <summary>
/// Constructor for class Mesh
/// </summary>
Mesh::Mesh() : VAO(0), VBO(0), IBO(0), indexCount(0), indices(), vertices() {}

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
	this->vertices = vertices;
	this->indices = indices;
	Create();
}

Mesh::Mesh(Primitive primitiveType)
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
	switch (primitiveType)
	{
		case PLANE:
			indices =
			{
				0, 2, 1,
				1, 2, 3
			};
			vertices =
			{
				-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
				10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
				-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
				10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
			};
			break;
		case PYRAMID: 
			indices =
			{
				0, 3, 1,
				1, 3, 2,
				2, 3, 0,
				0, 1, 2
			};

			vertices =
			{
				//    x      y      z		 u     v		 r     g     b
					-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
					 0.0f, -1.0f,  1.0f,	0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
					 1.0f, -1.0f, -0.6f,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
					 0.0f,  1.0f,  0.0f,	0.5f, 1.0f,		0.0f, 0.0f, 0.0f
			};
			AverageNormals(8, 5);
			break;
		case CUBE: 
			indices =
			{
				// front
				0, 1, 2,
				2, 1, 3,
				// right
				2, 3, 5,
				5, 3, 7,
				// back
				5, 7, 4,
				4, 7, 6,
				// left
				4, 6, 0,
				0, 6, 1,
				// top
				4, 0, 5,
				5, 0, 2,
				// bottom
				1, 6, 3,
				3, 6, 7
			};

			vertices =
			{
				-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
				-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
				1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

				-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
				-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
			};
			break;
		case SPHERE: break;		
	}
	
	Create();
}



void Mesh::Create()
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

void Mesh::AverageNormals(unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		unsigned int in0 = indices[i + 0] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		float v1X = vertices[in1 + 0] - vertices[in0 + 0];
		float v1Y = vertices[in1 + 1] - vertices[in0 + 1];
		float v1Z = vertices[in1 + 2] - vertices[in0 + 2];

		float v2X = vertices[in2 + 0] - vertices[in0 + 0];
		float v2Y = vertices[in2 + 1] - vertices[in0 + 1];
		float v2Z = vertices[in2 + 2] - vertices[in0 + 2];

		glm::vec3 v1(v1X, v1Y, v1Z);
		glm::vec3 v2(v2X, v2Y, v2Z);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0 + 0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1 + 0] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2 + 0] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}
	for (size_t i = 0; i < vertices.size() / vLength; i++)
	{
		unsigned int nOffset = (i * vLength) + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset + 0] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
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