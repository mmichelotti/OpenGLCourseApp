#include "Material.h"

Material::Material()
{

}

Material::Material(GLfloat specular, GLfloat roughness)
{
	this->specular = specular;
	this->roughness = roughness;
}

void Material::Use(GLuint specularLocation, GLuint roughnessLocation)
{
	glUniform1f(specularLocation, specular);
	glUniform1f(roughnessLocation, roughness);
}
