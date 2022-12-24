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

void Mesh::generateWithTexture(std::vector<float>& vertexData, std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)) );
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

    float rad = 0.9f;
    float root3by2Rad = root3by2*rad;
    std::vector<float> vertexData = {
       1.0f, 0.0f,  //0
       rad, 0.0f,   //1

       0.5f, root3by2,  //2
       0.5f*rad, root3by2Rad,  //3

       -0.5f, root3by2,     //4
       -0.5f*rad, root3by2Rad,  //5

       -1.0f, 0.0f,     //6
       -rad, 0.0f,      //7

       -0.5f, -root3by2,    //8
       -0.5f*rad, -root3by2Rad,     //9

       0.5f, -root3by2,     //10
       0.5f*rad, -root3by2Rad,      //11
    };

    std::vector<unsigned int> indices = {
        0,2,1,1,2,3, 
        2,4,3,3,4,5,
        4,6,5,5,6,7,
        6,8,7,7,8,9,
        8,10,9,9,10,11,
        10,0,11,11,0,1
    };

    generate(vertexData, indices);
}

void Mesh::createHexagonBackgroundMesh()
{
    double root3 = sqrt(3);
    float root3by2 = (float)(root3/2.0f);
    
    std::vector<float> vertexData = {
        1.0f, 0.0f, // 0
        0.5f, root3by2, // 1
        -0.5f, root3by2, // 2
        -1.0f, 0.0f, // 3
        -0.5f, -root3by2, // 4
        0.5f, -root3by2, // 5
    };

    std::vector<unsigned int> indices = {
        5,0,1,
        4,5,1,
        4,1,2,
        4,2,3
    };

    generate(vertexData, indices);
}

void Mesh::createLetterQuadMesh()
{
/*    std::vector<float> vertexData = {
        // vertex       // texture
        -0.05f, 0.1f,  0.0f, 0.125f, // 0
        0.05f, 0.1f,   0.0625f, 0.125f,// 1
        -0.05f, -0.1f,  0.0f, 0.0f,// 2
        0.05f, -0.1f,  0.0625f, 0.0f,// 3
    };
*/
    std::vector<float> vertexData = {
        // vertex       // texture
        -0.5f, 1.0f,    0.0f, 0.125f,       // 0
        0.5f, 1.0f,     0.0625f, 0.125f,    // 1
        -0.5f, -1.0f,   0.0f, 0.0f,         // 2
        0.5f, -1.0f,    0.0625f, 0.0f,      // 3
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 1, 3,
 //       0, 1, 3, 3, 1, 2
    };

    generateWithTexture(vertexData, indices);
}

void Mesh::createScreenQuadMesh()
{
    std::vector<float> vertexData = {
        // vertex       //texture
        -1.0f, 1.0f,    0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, -1.0f,    1.0f, 0.0f,
        -1.0f, -1.0f,   0.0f, 0.0f,
    };

    std::vector<unsigned int> indices = {
        0, 1, 3, 3, 1, 2 
    };

    generateWithTexture(vertexData, indices);
}
