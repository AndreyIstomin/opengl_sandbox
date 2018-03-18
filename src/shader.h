#ifndef _SHADER_H_
#define _SHADER_H_

#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include "log.h"

class Shader
{
public:
	Shader(){}
	~Shader(){};

	bool setup(const GLchar* vertexPath, const GLchar* fragmentPath);
	bool reload();
	void use() { glUseProgram(m_shaderProgram); }
	void unuse(){ glUseProgram(0); }

	bool setUniform(float value, const char * name);

private:

	std::string m_vShaderPath;
	std::string m_fShaderPath;

	unsigned int m_shaderProgram = 0;

	bool loadShader(std::string & shaderSrc, const GLchar * path);
	bool compileShader(unsigned int & shader, std::string & shaderSrc, unsigned int shaderType, char * infoLog);
};

#endif // _SHADER_H_