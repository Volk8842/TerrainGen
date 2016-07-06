#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderProgram.h"

const std::string ShaderProgram::SHADER_FILE_PREFIX = "Shaders/";

const std::string ShaderProgram::getShaderCode(const char* file) 
{
	std::ifstream shaderFile;
	std::stringstream shaderCodeStream;
	std::string shaderCodeString;

	shaderFile.open(file);
	if (shaderFile.is_open()) {
		shaderCodeStream << shaderFile.rdbuf();
		shaderCodeString = shaderCodeStream.str();
		shaderFile.close();
	}
	else {
		throw Error::NoShaderFile();
	}
	return shaderCodeString;
}

GLuint ShaderProgram::compileShaderCode(const char* file, GLenum shaderType) 
{	
	GLuint shaderId = glCreateShader(shaderType);
	
	try {	
		std::string code = getShaderCode(file);		
		const GLchar* shaderCode = code.c_str();		
		glShaderSource(shaderId, 1, &shaderCode, NULL);
		glCompileShader(shaderId);
	}
	catch (...) {
		throw;
	}

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		throw Error::BadShaderFile();
	}
	return shaderId;
}

void ShaderProgram::compileShaderProgram(std::string vShader, std::string fShader)
{
	try {
		GLuint vertexShader = compileShaderCode((SHADER_FILE_PREFIX + vShader).c_str(), GL_VERTEX_SHADER);
		GLuint fragmentShader = compileShaderCode((SHADER_FILE_PREFIX + fShader).c_str(), GL_FRAGMENT_SHADER);
		m_program = glCreateProgram();
		glAttachShader(m_program, vertexShader);
		glAttachShader(m_program, fragmentShader);
		glLinkProgram(m_program);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch (...) {
		throw;
	}

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw Error::BadShaderProgram();
	}
}

void ShaderProgram::use()
{
	glUseProgram(m_program);
}

GLuint ShaderProgram::program()
{
	return m_program;
}
