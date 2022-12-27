#include "FontRenderer.h"

FontRenderer::FontRenderer() : shader("font")
{
    shader.mapUniform("atlas");
    shader.mapUniform("size");
    shader.mapUniform("offset");
    shader.mapUniform("position");
    shader.mapUniform("shift");
    shader.mapUniform("index");
    shader.mapUniform("textColor");

    shader.mapUniform("debug");
    shader.mapUniform("scale");
    shader.mapUniform("ortho");
}

FontRenderer::~FontRenderer()
{}

void FontRenderer::render(FontAtlas& fontAtlas, Hexagons& hexagons, float ortho[16], Color& textColor, Color& selectedTextColor, unsigned int selectedIndex)
{
    shader.use();
    fontAtlas.useFontMesh();
    shader.setUniform("atlas", 0);
    shader.setUniform("scale", scale);
    shader.setUniform("ortho", ortho);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fontAtlas.getTextureId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    float gap = 1.0f;
    
    for(unsigned int h=0; h<7; h++)
    {
        if(h == selectedIndex)
        {
            shader.setUniform("textColor", selectedTextColor.r, selectedTextColor.g, selectedTextColor.b);
        }
        else
        {
            shader.setUniform("textColor", textColor.r, textColor.g, textColor.b);
        }
        std::string str = hexagons.str[h];
        float posX = hexagons.x[h];
        float posY = hexagons.y[h];
        shader.setUniform("position",posX,posY);
        shader.setUniform("shift",0.0f - str.length()/2.0f,0.0f);
        float totalWidth = 0;
        for(unsigned int i=0; i<str.length(); i++)
        {
            char ch = str[i];
            float width = (fontAtlas.width.find(ch) == fontAtlas.width.end()) ? 1.0f : fontAtlas.width[ch];
            shader.setUniform("size", width, 1.0f);
            float yOffset = (fontAtlas.yOffset.find(ch) == fontAtlas.width.end() ? 0.0f : fontAtlas.yOffset[ch]);
            shader.setUniform("offset", totalWidth, -yOffset*2);
            int yIndex = (ch - ' ')/16;
            int xIndex = (ch - ' ')%16;
            shader.setUniform("index", (float)xIndex, (float)yIndex); 
            
            shader.setUniform("debug", 1.0f);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

     /*       shader.setUniform("debug", -1.0f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    */
            totalWidth += (width + gap)*0.5f;
        }
     
    }
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    fontAtlas.unuseFontMesh();
    shader.unuse();

}
