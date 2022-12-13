#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(std::string name): name(name)
{
    std::string path = std::string("/usr/share/Hex/") + "res/shaders/";
	std::string vertexFile(path + name + ".vs");
	std::string fragmentFile(path + name + ".fs");
	programID = glCreateProgram();
	createShader(vertexID, GL_VERTEX_SHADER, vertexFile);
	createShader(fragmentID, GL_FRAGMENT_SHADER, fragmentFile);

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	int success;
	char infoLog[256];
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "Failed to link " << name << " \n " << infoLog << std::endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);	
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::createShader(unsigned int& shaderID, int shaderType, std::string filename)
{
    std::ifstream file(filename);

	if(file.bad())
	{
		std::cerr << filename << " not found " << std::endl;
		return;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string shaderCode = buffer.str();
	buffer.clear();
	file.close();

	shaderID = glCreateShader(shaderType);
	const char* cshaderCode = shaderCode.c_str();
	glShaderSource(shaderID, 1, &cshaderCode, NULL);
	glCompileShader(shaderID);

	int success;
	char infoLog[256];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 256, NULL, infoLog);
		std::cerr << "Failed to compile " << filename << " \n " << infoLog << std::endl;
	}

}

void ShaderProgram::use()
{
    glUseProgram(programID);
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}

void ShaderProgram::mapUniform(std::string uniformName)
{
    
	const char* cUniform = uniformName.c_str();
	int uniformLoc = glGetUniformLocation(programID, cUniform);
	uniformMap.insert(std::pair <std::string,int> (uniformName, uniformLoc));
}

void ShaderProgram::setUniform(std::string uniformName, int value)
{
    glUniform1i(uniformMap[uniformName], value);
}

void ShaderProgram::setUniform(std::string uniformName,float value)
{
    glUniform1f(uniformMap[uniformName], value);
}

void ShaderProgram::setUniform(std::string uniformName, float x, float y)
{
    glUniform2f(uniformMap[uniformName], x, y);
}

void ShaderProgram::setUniform(std::string uniformName, float r, float g, float b)
{
    glUniform3f(uniformMap[uniformName], r, g, b);
}


void ShaderProgram::setUniform(std::string uniformName, float r, float g, float b, float a)
{
    glUniform4f(uniformMap[uniformName], r, g, b, a);
}

