#ifndef H_SHATKON_RENDERER_H
#define H_SHATKON_RENDERER_H

#include "ShaderProgram.h"
#include <vector>
#include "Mesh.h"
#include "Hexagons.h"

class HexagonRenderer
{
    private:
        ShaderProgram shader;
    public:
        HexagonRenderer();
        ~HexagonRenderer();
        void render(Mesh* mesh);
        void render(Hexagons& hexagons);
};

#endif
