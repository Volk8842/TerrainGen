#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

#include <opengl.h>

namespace Error {
	struct NoShaderFile: public std::exception{};
	struct BadShaderFile: public std::exception{};
	struct BadShaderProgram: public std::exception{};
}

class ShaderProgram {	
public:
	void compileShaderProgram(std::string vShader, std::string fShader);
	void use();
	GLuint program();

private:	
	const std::string getShaderCode(const char* file);
	GLuint compileShaderCode(const char* file, GLenum shaderType);

	static const std::string SHADER_FILE_PREFIX;

	GLuint m_program;
};

#endif //SHADERPROGRAM_H 
