#include "IconRenderer.h"


IconRenderer::IconRenderer() : shader("icon")
{
  iconMesh.createScreenQuadMesh();
  shader.mapUniform("position");
  shader.mapUniform("scale");
  shader.mapUniform("ortho");
  shader.mapUniform("image");
  shader.mapUniform("textColor");
  shader.mapUniform("imageWH");
  shader.mapUniform("iconState");
}

IconRenderer::~IconRenderer()
{
}

void IconRenderer::render(Hexagons& hexagons, float ortho[16], Color& textColor, Color& selectedTextColor, unsigned int selectedIndex, int iconState)
{
  shader.use();
  iconMesh.use();
  shader.setUniform("image", 0);
  shader.setUniform("scale", scale);
  shader.setUniform("ortho", ortho);
  shader.setUniform("iconState", iconState);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  
  for(unsigned int h=1; h<7; h++)
  {
    if(!hexagons.hasIcon[h])
      continue;

    if(h == selectedIndex)
    {
      shader.setUniform("textColor", selectedTextColor.r, selectedTextColor.g, selectedTextColor.b); 
    }
    else 
    {
      shader.setUniform("textColor", textColor.r, textColor.g, textColor.b);     
    }

    shader.setUniform("position", hexagons.x[h], hexagons.y[h] + shiftY);
    shader.setUniform("imageWH", hexagons.icon[h].getWidth(), hexagons.icon[h].getHeight());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hexagons.icon[h].getTextureId());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  }
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  iconMesh.unuse();
  shader.unuse();
}
