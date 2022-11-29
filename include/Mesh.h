#ifndef H_ME55Y_10_H
#define H_ME55Y_10_H

#include "allgl.h"
#include <vector>
#include <string>
#include <math.h>

class Mesh
{
    private:
        unsigned int vao, vbo, ebo;
        int numOfIndices = 0;
        void generate(std::vector<float>&, std::vector<unsigned int>&);
    public:
        Mesh();
        ~Mesh();
        void use();
        void unuse();
        int getNumOfIndices();

        void createHexagonMesh();

};

#endif
