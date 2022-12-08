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
    glDrawElements(GL_TRIANGLES, mesh->getNumOfIndices(), GL_UNSIGNED_INT, 0);
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
       shader.setUniform("color", hexagons.r[i], hexagons.g[i], hexagons.b[i], 1.0f);
       shader.setUniform("size", hexagons.size[i]);

       glDrawElements(GL_TRIANGLES, hexagons.meshIndicesCount(), GL_UNSIGNED_INT, 0); 
    }

    glDisableVertexAttribArray(0);
    hexagons.unuseMesh();
    shader.unuse();
}

void HexagonRenderer::renderBg(Hexagons& hexagons, int selectedIndex)
{
    shader.use();
    hexagons.useBgMesh();
    glEnableVertexAttribArray(0);

    for(unsigned int i=0; i<hexagons.x.size(); i++)
    {
       shader.setUniform("position", hexagons.x[i], hexagons.y[i]);
       shader.setUniform("color",0.0f, 0.0f, 0.0f, 0.8f);
       if(selectedIndex >= 0 && selectedIndex == i)
       {
            shader.setUniform("color", 0.1f, 0.1f, 0.1f, 0.8f);
       }
       shader.setUniform("size", hexagons.size[i]);

       glDrawElements(GL_TRIANGLES, hexagons.bgMeshIndicesCount(), GL_UNSIGNED_INT, 0); 
    }

    glDisableVertexAttribArray(0);
    hexagons.unuseBgMesh();
    shader.unuse();
}
