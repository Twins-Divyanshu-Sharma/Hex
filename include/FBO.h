#ifndef H_FBO_H
#define H_FBO_H

#include "allgl.h"
#include <iostream>

#define max_attachments 4

class FBO
{
    private:
        unsigned int fboID;
        unsigned int texID[max_attachments];
        unsigned int texIDSize = 0;
    public:
        FBO();
        ~FBO();
        void bind();
        void unbind();
        void attachTexture(unsigned int width, unsigned int height);
        void lockAttachments();
        unsigned int getAttachment(unsigned int);
};

#endif
