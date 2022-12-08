#include "FontAtlas.h"

FontAtlas::FontAtlas()
{
    width['!'] = 0.5f;    
    width['\''] = 0.5f;
    width['('] = 0.5f;
    width[')'] = 0.5f;
    width[','] = 0.5f;
    width['.'] = 0.5f;
    width[':'] = 0.5f;
    width[';'] = 0.5f;
    width['['] = 0.5f;
    width[']'] = 0.5f;
    width['^'] = 0.5f;
    width['`'] = 0.5f;
    width['i'] = 0.5f;
    width['j'] = 0.5f;
    width['l'] = 0.5f;
    width['t'] = 0.5f;
    width['{'] = 0.5f;
    width['}'] = 0.5f;
    width['|'] = 0.5f;

    yOffset['g'] = 0.25f;
    yOffset['j'] = 0.25f;
    yOffset['p'] = 0.25f;
    yOffset['q'] = 0.25f;
    yOffset['y'] = 0.25f;
    yOffset[','] = 0.25f;

    mesh.createQuadMesh();

}

FontAtlas::~FontAtlas()
{}


unsigned int FontAtlas::getTextureId()
{
    return texture->getTextureId();
}

void FontAtlas::useFontMesh()
{
    mesh.use();
}

void FontAtlas::unuseFontMesh()
{
    mesh.unuse();
}

void FontAtlas::setAtlas(std::string name)
{
    texture = new Texture(name);
}
