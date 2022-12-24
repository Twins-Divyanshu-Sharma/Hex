#include "ScreenQuadRenderer.h"

ScreenQuadRenderer::ScreenQuadRenderer() : shader("screen")
{
    shader.mapUniform("colorTexture");
    shader.mapUniform("blurTexture");
}

ScreenQuadRenderer::~ScreenQuadRenderer()
{}

void ScreenQuadRenderer::render(Mesh& mesh, FBO& fbo, FBO& blurFbo)
{
    shader.use();
    shader.setUniform("colorTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo.getAttachment(0));
    shader.setUniform("blurTexture", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, blurFbo.getAttachment(0));
    mesh.use();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    mesh.unuse();
    
    shader.unuse();
}
