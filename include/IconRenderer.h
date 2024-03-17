#ifndef H_ICON_RENDERER_H
#define H_ICON_RENDERER_H

#include "Mesh.h"
#include <vector>
#include "ShaderProgram.h"
#include "Hexagons.h"
#include "Color.h"

class IconRenderer 
{
private:
  Mesh iconMesh;
  ShaderProgram shader;
  float scale = 0.5f;
  float shiftY = 1.0f;
public:
  IconRenderer();
  ~IconRenderer();
  void render(Hexagons& hexagons, float ortho[16], Color& textColor, Color& selectedTextColor, unsigned int selectedIndex, int iconState);
   
};


#endif
