#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "opengl.h"

namespace Error 
{
	struct NoShaderFile: public std::exception{};
	struct BadShaderFile: public std::exception{};
	struct BadShaderProgram: public std::exception{};
}

class ShaderProgram 
{	
public:
	void compileShaderProgram();
	void use();
	GLuint program();

private:	
	const std::string getShaderCode(const char* file);
	GLuint compileShaderCode(const char* file, GLenum shaderType);

	GLuint m_program;
};

#endif //SHADERPROGRAM_H 
