#ifndef H_BLOOM_RENDERER_H
#define H_BLOOM_RENDERER_H

#include "ShaderProgram.h"
#include "Mesh.h"
#include "FBO.h"

class BloomRenderer
{
    private:
        ShaderProgram blurShader;
        const int blurAmount = 5;
    public:
        BloomRenderer();

        ~BloomRenderer();
        void render(Mesh& mesh, FBO& fbo, FBO& ping, FBO& pong);
};

#endif
