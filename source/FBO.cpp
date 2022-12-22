#include "FBO.h"

FBO::FBO()
{
    glGenFramebuffers(1, &fboID);
}

FBO::~FBO()
{
    glDeleteFramebuffers(1, &fboID);
}

void FBO::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void FBO::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::attachTexture(unsigned int width, unsigned int height)
{
    bind();
    
    glGenTextures(1, &texID[texIDSize]);
    glBindTexture(GL_TEXTURE_2D, texID[texIDSize]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + texIDSize, GL_TEXTURE_2D, texID[texIDSize], 0);

    texIDSize++;

    unbind();

}

void FBO::lockAttachments()
{
    bind();

    unsigned int* attachments = new unsigned int[texIDSize];
    for(unsigned int i=0; i<texIDSize; i++)
    {
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    glDrawBuffers(texIDSize, attachments);
    delete [] attachments;

    unbind();
}

unsigned int FBO::getAttachment(unsigned int x)
{
    if(x < texIDSize)
        return texID[x];
    else
    {
        std::cerr << "fbo attachment index out of bounds" << std::endl;
        return 0;
    }
}
