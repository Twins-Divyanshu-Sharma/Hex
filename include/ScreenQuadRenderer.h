#ifndef H_SCREEN_QUAD_RENDERER_H
#define H_SCREEN_QUAD_RENDERER_H


#include "ShaderProgram.h"
#include "Mesh.h"
#include "FBO.h"

class ScreenQuadRenderer
{
    private:
        ShaderProgram shader;
    public:
        ScreenQuadRenderer();
        ~ScreenQuadRenderer();
        void render(Mesh& mesh, FBO& fbo, FBO& blurFBO);
};

#endif
