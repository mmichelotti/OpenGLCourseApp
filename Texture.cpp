#include "Texture.h"

void Texture::Initialize()
{
    ID = 0;
    size = Vec2<int>(0, 0);
    bitDepth = 0;
    fileLocation = "";
}

Texture::Texture()
{
    Initialize();
}

Texture::Texture(const char* fileLocation)
{
    Initialize();
    this->fileLocation = fileLocation;
}

void Texture::Load()
{
    unsigned char* texData = stbi_load(fileLocation, &size.x, &size.y, &bitDepth, 0);
    if (!texData)
    {
        printf("Failed to find %s\n", fileLocation);
    }
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //texture repeat along x axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //texture repeat along y axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //blend pixel together, GL_NEAREST keep pixelated
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT); //texture repeat along x axis

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    //unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texData);
}

void Texture::Use()
{
    //the sampler pass through the texture texture unit "GL_TEXTURE0" 1 / 2 / 3.... 32
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Clear()
{
    glDeleteTextures(1, &ID);
    Initialize();
}

Texture::~Texture()
{
    Clear();
}

