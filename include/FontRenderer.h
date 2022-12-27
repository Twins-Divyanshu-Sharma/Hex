#ifndef H_LIPI_R3ND3R3R_H
#define H_LIPI_R3ND3R3R_H


#include "FontAtlas.h"
#include "ShaderProgram.h"
#include "Hexagons.h"
#include "Color.h"

class FontRenderer
{
    private:
        ShaderProgram shader;
        float scale = 0.3f;
        // clean all 
        // Q O i n s t x \ / 1 4 5
    public:
        FontRenderer();
        ~FontRenderer();
        void render(FontAtlas& fontAtlas, Hexagons& hexagons, float ortho[16], Color& textColor, Color& selectedTextColor, unsigned int selectedIndex);
};

#endif
