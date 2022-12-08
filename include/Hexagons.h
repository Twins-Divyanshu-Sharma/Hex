#ifndef H_ANEK_SHATKON_H
#define H_ANEK_SHATKON_H

#include "Mesh.h"
#include <vector>

class Hexagons
{
    private:
        Mesh mesh;
        Mesh backgroundMesh;
    public:
        Hexagons();
        ~Hexagons();
        std::vector<float> x, y;
        std::vector<float> r, g, b;
        std::vector<float> size;
        std::vector<std::string> str;

        void useMesh();
        void unuseMesh();
        int meshIndicesCount();

        void insert(float x, float y, float r, float g, float b, float size);

        void useBgMesh();
        void unuseBgMesh();
        int bgMeshIndicesCount();
};

#endif
