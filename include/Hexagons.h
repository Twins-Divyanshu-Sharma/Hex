#ifndef H_ANEK_SHATKON_H
#define H_ANEK_SHATKON_H

#include "Mesh.h"
#include <vector>

class Hexagons
{
    private:
        Mesh mesh;
    public:
        Hexagons();
        ~Hexagons();
        std::vector<float> x, y;
        std::vector<float> r, g, b;
        std::vector<float> size;

        void useMesh();
        void unuseMesh();
        int meshIndicesCount();

        void insert(float x, float y, float r, float g, float b, float size);
};

#endif
