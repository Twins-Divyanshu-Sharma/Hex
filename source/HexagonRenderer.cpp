#include "HexagonRenderer.h"

HexagonRenderer::HexagonRenderer() : shader("hexagon")
{
    shader.mapUniform("color");
    shader.mapUniform("position");
    shader.mapUniform("size");
    shader.mapUniform("neon");
    shader.mapUniform("ortho");
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
    shader.setUniform("neon", 1.0f);
    mesh->use();
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, mesh->getNumOfIndices(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    mesh->unuse();
}


void HexagonRenderer::render(Hexagons& hexagons, float ortho[16])
{
    shader.use();
    hexagons.useMesh();
    glEnableVertexAttribArray(0);

    for(unsigned int i=0; i<hexagons.x.size(); i++)
    {
       shader.setUniform("position", hexagons.x[i], hexagons.y[i]);
       shader.setUniform("color", hexagons.r[i], hexagons.g[i], hexagons.b[i], 1.0f);
       shader.setUniform("size", hexagons.size[i]);
       shader.setUniform("neon", 1.0f);
       shader.setUniform("ortho", ortho);
       glDrawElements(GL_TRIANGLES, hexagons.meshIndicesCount(), GL_UNSIGNED_INT, 0); 
    }

    glDisableVertexAttribArray(0);
    hexagons.unuseMesh();
    shader.unuse();
}

void HexagonRenderer::renderBg(Hexagons& hexagons, int selectedIndex, float ortho[16], Color& visualColor)
{
    shader.use();
    hexagons.useBgMesh();
    glEnableVertexAttribArray(0);

    for(unsigned int i=0; i<hexagons.x.size(); i++)
    {
       shader.setUniform("position", hexagons.x[i], hexagons.y[i]);
       shader.setUniform("color",0.0f, 0.0f, 0.0f, 1.0f);
       shader.setUniform("neon", 0.0f);
       shader.setUniform("size", hexagons.size[i]+0.15f*hexagons.size[i]);
       shader.setUniform("ortho", ortho);
       glDrawElements(GL_TRIANGLES, hexagons.bgMeshIndicesCount(), GL_UNSIGNED_INT, 0); 
    }

    if(selectedIndex >= 0 )
    {
        shader.setUniform("position", hexagons.x[selectedIndex], hexagons.y[selectedIndex]);
        shader.setUniform("color", visualColor.r, visualColor.g, visualColor.b, 1.0f);
        shader.setUniform("neon", 0.0f);
        shader.setUniform("size", hexagons.size[selectedIndex]);
        shader.setUniform("ortho", ortho);
        glDrawElements(GL_TRIANGLES, hexagons.bgMeshIndicesCount(), GL_UNSIGNED_INT, 0); 
    }

    glDisableVertexAttribArray(0);
    hexagons.unuseBgMesh();
    shader.unuse();
}
