#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
}

Texture::Texture(std::string name)
{
	std::string path = "res/textures/" + name + ".png";
	this->name = name;

	const char* cTarget = path.c_str();
	
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(cTarget, &width, &height, &channels, 0);
	if (data == nullptr)
	{
		std::cerr << "Texture not found : " << path << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

unsigned int Texture::getTextureId()
{
	return id;
}

std::string& Texture::getName()
{
	return name;
}
