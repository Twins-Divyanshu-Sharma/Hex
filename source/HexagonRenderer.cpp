#include "HexagonRenderer.h"

HexagonRenderer::HexagonRenderer() : shader("hexagon")
{
    shader.mapUniform("color");
    shader.mapUniform("position");
    shader.mapUniform("size");
}

HexagonRenderer::~HexagonRenderer()
{

}

void HexagonRenderer::render(Mesh* mesh)
{
    shader.use();
    shader.setUniform("position", 0, 0);
    shader.setUniform("color", 0, 0, 1.0f);
    shader.setUniform("size", 1.0f);
    mesh->use();
    glEnableVertexAttribArray(0);
    glDrawElements(GL_LINE_STRIP, mesh->getNumOfIndices(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    mesh->unuse();
}


void HexagonRenderer::render(Hexagons& hexagons)
{
    shader.use();
    hexagons.useMesh();
    glEnableVertexAttribArray(0);

    for(unsigned int i=0; i<hexagons.x.size(); i++)
    {
       shader.setUniform("position", hexagons.x[i], hexagons.y[i]);
       shader.setUniform("color", hexagons.r[i], hexagons.g[i], hexagons.b[i]);
       shader.setUniform("size", hexagons.size[i]);

       glDrawElements(GL_LINE_STRIP, hexagons.meshIndicesCount(), GL_UNSIGNED_INT, 0); 
    }

    glDisableVertexAttribArray(0);
    hexagons.unuseMesh();
    shader.unuse();
}
