#include "Hexagons.h"

Hexagons::Hexagons()
{
    mesh.createHexagonMesh();
}

Hexagons::~Hexagons()
{}

void Hexagons::useMesh()
{
    mesh.use();
}

void Hexagons::unuseMesh()
{
    mesh.unuse();
}

int Hexagons::meshIndicesCount()
{
    return mesh.getNumOfIndices();
}

void Hexagons::insert(float x, float y, float r, float g, float b, float size)
{
  this->x.push_back(x);  
  this->y.push_back(y);
  this->r.push_back(r);
  this->g.push_back(g);
  this->b.push_back(b);
  this->size.push_back(size);
}
