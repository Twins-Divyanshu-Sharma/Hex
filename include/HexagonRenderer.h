#ifndef H_SHATKON_RENDERER_H
#define H_SHATKON_RENDERER_H

#include "ShaderProgram.h"
#include <vector>
#include "Mesh.h"
#include "Hexagons.h"
#include "Color.h"

class HexagonRenderer
{
    private:
        ShaderProgram shader;
    public:
        HexagonRenderer();
        ~HexagonRenderer();
        void render(Mesh* mesh);
        void render(Hexagons& hexagons, float ortho[16]);
        void renderBg(Hexagons& hexagons, int selectedIndex, float ortho[16], Color& visualColor);
};

#endif
