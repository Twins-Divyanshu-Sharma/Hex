#include "BloomRenderer.h"

BloomRenderer::BloomRenderer() : blurShader("blur")
{
    blurShader.mapUniform("image");
    blurShader.mapUniform("horizontal");
}

BloomRenderer::~BloomRenderer()
{}

void BloomRenderer::render(Mesh& mesh, FBO& fbo, FBO& ping, FBO& pong)
{
    blurShader.use();
    mesh.use();
    for(int i=0; i<blurAmount; i++)
    {

        ping.bind();
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        blurShader.setUniform("imageTex", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, i ==0 ? fbo.getAttachment(1) : pong.getAttachment(0));
        blurShader.setUniform("horizontal", 1.0f);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        ping.unbind();


        pong.bind();
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        blurShader.setUniform("imageTex", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ping.getAttachment(0));
        blurShader.setUniform("horizontal", 0.0f);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        pong.unbind();

    }

    mesh.unuse();
    blurShader.unuse();
}
