#include "Mesh.h"

Mesh::Mesh()
{}

Mesh::~Mesh()
{}

void Mesh::use()
{
    glBindVertexArray(vao);
}

void Mesh::unuse()
{
    glBindVertexArray(0);
}

int Mesh::getNumOfIndices()
{
    return numOfIndices;
}

void Mesh::generate(std::vector<float>& vertexData, std::vector<unsigned int>& indices)
{
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);

	numOfIndices = indices.size();

}

void Mesh::createHexagonMesh()
{
    double root3 = sqrt(3);
    float root3by2 = (float)(root3/2.0f);
    std::vector<float> vertexData = {
       1.0f, 0.0f,  
       0.5f, root3by2,
       -0.5f, root3by2,
       -1.0f, 0.0f,
       -0.5f, -root3by2,
       0.5f, -root3by2,
    };

    std::vector<unsigned int> indices = {
        0,1,2,3,4,5,0
    };

    generate(vertexData, indices);
}
