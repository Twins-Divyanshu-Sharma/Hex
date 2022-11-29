#ifndef H_SH4D3R_PR0GR4M_H
#define H_SH4D3R_PR0GR4M_H

#include "allgl.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

class ShaderProgram
{
    private:
        std::string name; 
        std::map<std::string,int> uniformMap;
        unsigned int programID, fragmentID, vertexID;
        void createShader(unsigned int&, int, std::string);
    public:
        ShaderProgram(std::string);
        ~ShaderProgram();
        void use();
        void unuse();
        void mapUniform(std::string);

        void setUniform(std::string, int);
        void setUniform(std::string, float);
        void setUniform(std::string, float, float);
        void setUniform(std::string, float, float, float);
};

#endif
