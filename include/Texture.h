#ifndef H_T3XTUR3_H
#define H_T3XTUR3_H

#include "allgl.h"
#include <iostream>
#include <string>

class Texture
{
private:
	unsigned int id;
	int width, height, channels;
	unsigned char* data;
	std::string name;
public:
	Texture();
	Texture(std::string name);
	~Texture();
	unsigned int getTextureId();
	std::string& getName();
};

#endif
