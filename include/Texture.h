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

  Texture(std::string, int useless);
public:
	Texture();
	Texture(std::string name);
	~Texture();
	unsigned int getTextureId();
	std::string& getName();
  
  static Texture loadFromPath(std::string);

  int recreateFromPath(std::string);
  bool loaded = true;

  int getWidth();
  int getHeight();

};

#endif
