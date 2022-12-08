#ifndef H_LIPI_4TL4S_H
#define H_LIPI_4TL4S_H

#include "Texture.h"
#include "Mesh.h"
#include <map>

class FontAtlas
{
    private:
        Texture* texture;
        Mesh mesh;
    public:
        FontAtlas();
        ~FontAtlas();
        void setAtlas(std::string);
        unsigned int getTextureId();
        std::map<char,float> width;
        std::map<char,float> yOffset;
        void useFontMesh();
        void unuseFontMesh();

};


#endif
